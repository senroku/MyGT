#pragma once
#include <memory>
#include <memory_resource>
#include <vector>
#include <string>
#include <concepts>
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
		//コンセプトにした方がいいのでは？.
		static_assert(sizeof...(Args) > 0, "notting template Args");
		static_assert(MyTU::is_all_base_of_v<PrivateSpace::GameObjectManagerInrterface, Args>, "is not GameObjectManager of Args");

		Sean(std::pmr::memory_resource* gallocator) :m_resouse(gallocator)
		{
			add_game_manager(m_gameManager);
		};
		virtual ~Sean() {}

	public:
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
		//template<typename T>
		//void add_game_object_manager(T* gom) {
		//	static_assert(std::is_base_of_v<PrivateSpace::GameObjectManagerInrterface, T>, "T is not GameObjectManager extended interface class");
		//}

		//自動作成を考慮中.
		//tupleだとgetが必須add
		template<typename T, std::size_t N = -1>
		constexpr T* create_game_object()
		{
			static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
			T* result = nullptr;
			//自動制御のためにis_hogehogeを調べて自動で入るように.
			if constexpr (N == -1) {
				std::get<0>(m_gameManager).create_game_object<T>();
			}
			else
			{
				static_assert(N < sizeof...(Args), "Over Args");
				std::get<N>(m_gameManager).create_game_object<T>();
			}
			return result;
		}
		template<typename T, typename GOM>
		requires std::derived_from<GOM, PrivateSpace::GameObjectManagerInrterface>
		constexpr T* create_game_object()
		{
			static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
			static_assert(std::is_base_of_v<PrivateSpace::GameObjectManagerInrterface, GOM>, "T is not Sean extended interface class");
			T* result = nullptr;
			//自動制御のためにis_hogehogeを調べて自動で入るように.
			std::get<GOM>(m_gameManager).create_game_object<T>();
			return result;
		}
	private:
		template <std::size_t N = 0,typename T>
		constexpr void add_game_manager(const T& t){
			if constexpr (N < std::tuple_size_v<T>) {
				m_p_gameManager[N] = ((PrivateSpace::GameObjectManagerInrterface*)&(std::get<N>(t)));
				add_game_manager<N + 1>(t);
			}
		}
	protected:
		//不要な場合があるので.
		//フレームの最後に破棄作成する場合は使うべき.
		virtual void object_deleate_create() {};

	protected:
		std::pmr::memory_resource* m_resouse;
		std::array<PrivateSpace::GameObjectManagerInrterface*, sizeof...(Args)> m_p_gameManager;
		std::tuple<Args...> m_gameManager;
	};

}
