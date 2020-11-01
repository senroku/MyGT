#pragma once

#include "Component.h"
#include "Sprite.h"
#include "EBO.h"


namespace MyGT {

	//�K�v�̂���R���|�\�l���g�����m��.
//EXISTS�����܂����ƂƂ邢�����@�����邩������Ȃ����s���Ȃ̂�,
//�ʂ̃e���v���[�g�N���X������Ă���.
//�N�����@�������Ă�������.
	template <typename T, std::size_t N, bool EXISTS>
	struct ComponentArray_base {
		//���d�p���\�肾����֐��͂܂���.
		//template<typename T>constexpr bool EXIST() { return EXIST; }
		virtual ~ComponentArray_base() {}
	};

	template <typename T, std::size_t N, typename...Args>
	struct ComponentArray : public ComponentArray_base<T, N, MyTU::is_any_base_of_v<T, Args...>> {};


	//�������������ꍇGameObjectManager��Compnent���֒ǉ����邽��.
	template <std::size_t N>
	struct ComponentArray_base<Sprite, N, true> {
		std::array <SRC::Sprite, N > sprites;
	};


	template <std::size_t N, typename...Args>
	struct EMPTY_BASES  ComponentManager
		: public ComponentArray<Sprite, N, Args...>
//		, public ComponentArray<Component, N, Args...>
	{
		constexpr static bool isSprites = MyTU::is_any_base_of_v<Sprite, Args...>;

		ComponentManager() = default;

		void start() {}
		//�R���|�[�l���g��UpdateGO�̃A�b�v�f�[�g��ɂ܂Ƃ߂ď���.
		void update() {
			if constexpr (isSprites) {
				void* p = &(this->sprites);
			}
			//else if constexpr ()
			//else
		}
	};

}