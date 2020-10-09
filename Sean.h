#pragma once
#include <memory>
#include <memory_resource>
#include <vector>
#include <string>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SeanManager.h"
//#include "GameObjectAllocator.h"

//Seanは1フレームに一回のみの呼び出し.
namespace MyGT {
	struct SeanInterface {
		virtual void start() = 0;
		virtual void update() = 0;
	};

	//Variant風.
	template<typename...Args>
	struct Sean : public SeanInterface
	{
		static_assert(sizeof...(Args) > 0, "notting template Args");
		static_assert(MyTU::is_all_base_of_v<GameObjectManagerInrterface, Args>, "is not GameObjectManager of Args");

		Sean(std::pmr::memory_resource* gallocator) :m_resouse(gallocator)
		{
			addGameManager(m_gameManager);
		};
		virtual ~Sean() {}

	public:
		template<typename T>
		void addManager(T* gom) {
			static_assert(std::is_base_of_v<GameObjectManagerInrterface, T>, "T is not GameObjectManager extended interface class");
		}
		virtual void start() {
			for (auto gmanger : m_p_gameManager) {
				gmanger->start();
			}
		}
		virtual void update() {
			for (auto gmanger : m_p_gameManager) {
				gmanger->update();
			}
		}
		//自動作成を考慮中.
		//tupleだとgetが必須add
		template<typename T, std::size_t N = -1>
		constexpr GameObject* createGameObject()
		{
			static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
			GameObject* result = nullptr;
			//自動制御のためにis_hogehogeを調べて自動で入るように.
			if constexpr (N == -1) {
				std::get<0>(m_gameManager).createGameObject<T>();
			}
			else
			{
				static_assert( N < sizeof...(Args), "Over Args");
				std::get<N>(m_gameManager).createGameObject<T>();
			}
			return result;
		}
	private:
		template <std::size_t N = 0,typename T>
		constexpr void addGameManager(const T& t){
			if constexpr (N < std::tuple_size_v<T>) {
				m_p_gameManager[N] = ((GameObjectManagerInrterface*)&(std::get<N>(t)));
				addGameManager<N + 1>(t);
			}
		}
	protected:
		//不要な場合があるので.
		//フレームの最後に破棄作成する場合は使うべき.
		virtual void objectDeleateCreate() {};

	protected:
		std::pmr::memory_resource* m_resouse;
		std::array<GameObjectManagerInrterface*, sizeof...(Args)> m_p_gameManager;
		std::tuple<Args...> m_gameManager;
	};

}
