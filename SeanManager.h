#pragma once
#include "Sean.h"
#include "SeanAllocator.h"

//Sean�̃������Ǘ��N���X.
namespace MyGT {
	template<std::size_t N>
	struct SeanManager
	{
		//�R�s�[,���[�u�̋֎~.
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

		//stack�Ȃ̂�.
		int pop_back() {
			//�폜���̃T�C�Y�ǂ�����?
			resourse.deallocate(pSeans.back().first, pSeans.back().second);
			pSeans.pop_back();
			return 0;
		}

	public:


	private:
		//���͂�����Vector�̓��������C�A�E�g�O.
		std::vector<std::pair<SeanInterface*, size_t>> pSeans;
		stack_resource<N> resourse;
	};
}