#pragma once
#include <concepts>
#include "Sean.h"
#include "SeanAllocator.h"

//Seanのメモリ管理クラス.
namespace MyGT {

	constexpr std::size_t GAME_MAX_SIZE = 16777216;

	//SeanManagerを複数使うべき場面が不明だから.
	//プライベートにして隠してはいるが、複数でも一応動く.
	namespace PrivateSpace {
		struct SeanManagerInterface {
		};
		template<std::size_t N>
		struct SeanManager : public SeanManagerInterface
		{
			//コピー,ムーブの禁止.
			SeanManager(const SeanManager&) = delete;
			SeanManager& operator=(const SeanManager&) = delete;
			SeanManager(SeanManager&&) = delete;
			SeanManager& operator=(SeanManager&&) = delete;

			~SeanManager() {}

		private:
			SeanManager() = default;


		public:
			static inline SeanManager* get_instance() {
				static SeanManager instance;
				return &instance;
			}
			void start() {
				pSeans.back().first->start();
			}
			void update() {
				pSeans.back().first->update();
			}

			template<class T>
			SeanInterface* push_back() {
				static_assert(std::is_base_of_v<SeanInterface, T>, "T is not Sean extended interface class");
				void* p = resourse.allocate(sizeof(T));
				pSeans.push_back(
					//std::make_unique<T>(
					std::make_pair(
						(T*)new(p) T(&resourse),
						sizeof(T)
					)
				);
				return pSeans.back().first;
			}

			//SeanInterface* push_back(int n) {
			//	SeanInterface* sean = new Sean();
			//	return sean;
			//}

			//stackなので.
			int pop_back() {
				//削除時のサイズどうする?
				resourse.deallocate(pSeans.back().first, pSeans.back().second);
				pSeans.pop_back();
				return 0;
			}

			//ゲームオブジェクト生成用
			//ゲームオブジェクトを入れます.
			//SeanにてInterfaceを使用する場合実装不可.
			template<typename T, std::size_t N = -1>
			constexpr T* create_game_object() {
				return pSeans.back().first->create_game_object<T, N>();
			}

			template<typename T, typename GOM>
			requires std::derived_from<GOM, PrivateSpace::GameObjectManagerInrterface>
			constexpr T* create_game_object()
			{
				return pSeans.back().first->create_game_object<T, GOM>();
			}


		public:


		private:
			//今はここのVectorはメモリレイアウト外.
			std::vector<std::pair<SeanInterface*, size_t>> pSeans;
			stack_resource<N> resourse;
		};
	}

	using SeanManager = PrivateSpace::SeanManager<GAME_MAX_SIZE>;


	//template<typename T>
	//using addSean = SeanManager<GAME_MAX_SIZE>::get_instance()::push_back<T>();
	//template<typename T>
	//using addGameObject = SeanManager<GAME_MAX_SIZE>::get_instance()::push_back<T>();
}