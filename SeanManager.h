#pragma once
#include "Sean.h"
#include "SeanAllocator.h"

//Seanのメモリ管理クラス.
namespace MyGT {
	template<std::size_t N>
	struct SeanManager
	{
		//コピー,ムーブの禁止.
		SeanManager(const SeanManager&) = delete;
		SeanManager& operator=(const SeanManager&) = delete;
		SeanManager(SeanManager&&) = delete;
		SeanManager& operator=(SeanManager&&) = delete;

		SeanManager() = default;
		~SeanManager() {}

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
		Sean* push_back() {
			static_assert(std::is_base_of_v<Sean, T>, "T is not Sean extended interface class");
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

		Sean* push_back(int n) {
			Sean* sean = new Sean();
			return sean;
		}

		//stackなので.
		int pop_back() {
			//削除時のサイズどうする?
			resourse.deallocate(pSeans.back().first, pSeans.back().second);
			pSeans.pop_back();
			return 0;
		}

	public:


	private:
		//今はここのVectorはメモリレイアウト外.
		std::vector<std::pair<Sean*, size_t>> pSeans;
		stack_resource<N> resourse;
	};
}