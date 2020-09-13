#pragma once
#include "GameObject.h"
#include "Component.h"
#include <cstddef>
#include <algorithm>
#include <array>
#include <type_traits>

namespace MyGT {

	struct GameOvjectManagerInrterface {
		virtual void start() = 0;
		virtual void update() = 0;
	};
	template<typename...Args>
	struct Sizeof {
		constexpr static std::size_t max = std::max<std::size_t>({ sizeof(Args)... });
	};
	//���S�������܂�l�����ĂȂ��̂Ŋ�Ȃ�����.
	//GameObject���p�����Ă�����̂��ő�T�C�Y�̃N���X�̑傫���ɂ��āA
	//�z��Ŋm��.
	template<std::size_t N,typename... Args >
	struct GameObjectManager :public GameOvjectManagerInrterface
	{
		GameObjectManager():max_index(0){}
		~GameObjectManager(){}
	private:
		//GameObjectType�̍ő�T�C�Y���i�[���邽��.
		struct GameObjectBuffer {
			GameObject obj;
			//char buffer[value_size<Args>];
			std::byte buffer[Sizeof<GameObject,Args...>::max - sizeof(GameObject)];
		};

	public:
		void start() {
			for (int i = 0; i < max_index; i++)
				mobjs[i].obj.start();
		}
		void update() {
			for (int i = 0; i < max_index; i++)
				mobjs[i].obj.update();
		}
		template<typename T>
		void add() {
			new((void*)(&(mobjs[0]))) T();
			max_index++;
		}
	private:
		std::array<GameObjectBuffer,N> mobjs;
		std::size_t max_index;
		//�R���|�[�l���g�T�C�Y���s������Ȃ��H
		//Component</*Sean?*/> compornents[N];
	};
}