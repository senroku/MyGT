#pragma once
#include "GameObject.h"
#include "Component.h"
#include "TemplateUtil.h"
#include "Sprite.h"
#include "ComponentManager.h"
#include "EBO.h"
#include <cstddef>
#include <algorithm>
#include <array>
#include <type_traits>

namespace MyGT {

	namespace PrivateSpace {

		struct GameObjectManagerInrterface {
			virtual void start() = 0;
			virtual void update() = 0;
			// �R���|�[�l���g��ʔԍ����w��.
			//virtual void getComponent(int compornentID) = 0;
		};
	}



	//���S�������܂�l�����ĂȂ��̂Ŋ�Ȃ�����.
	//GameObject���p�����Ă�����̂��ő�T�C�Y�̃N���X�̑傫���ɂ��āA
	//�z��Ŋm��.
	//�R���|�[�l���g���g�p���Ȃ��ꍇ.
	// GameObjectManagerInrterface���Ȃ����T�C�Y�������Ă���H<-vptr�����Y�ꂩ�H.
	template<std::size_t N,typename... Args >
	struct EMPTY_BASES  GameObjectManager
		:public PrivateSpace::GameObjectManagerInrterface
		,public ComponentManager<N,Args...>	{
		static_assert(sizeof...(Args) > 0, "notting template Args");
		static_assert(MyTU::is_all_base_of_v<GameObject,Args...>, "is not base of Args");

		GameObjectManager():max_index(0){}
		virtual ~GameObjectManager(){}
	private:
		//GameObjectType�̍ő�T�C�Y���i�[���邽��.
		struct GameObjectBuffer {
			GameObjectBuffer() = default;
			GameObject obj;
			std::byte buffer[MyTU::Sizeof<GameObject,Args...>::max - sizeof(GameObject)];
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

		//�Q�[���I�u�W�F�N�g�����܂�.
		template<typename T>
		T* create_game_object() {
			static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
			T* result = new((void*)(&(mobjs[max_index]))) T();
			max_index++;
			return result;
		}
	public:
		std::array<GameObjectBuffer,N> mobjs;
		std::size_t max_index;
	};

	template<class T,std::size_t N>
	struct polyObjct {
		std::array<T, N> arrayObj;
	};

	template<class T, std::size_t N>
	struct GameObjectPoly {

		std::array<T, N> arrayObj;
	};

	//in compornent.
	//������.
	namespace inc {
		//GameObject���R���|�[�l���g�������Ă���O��.
		template<std::size_t N, typename... Args >
		struct GameObjectManager :public PrivateSpace::GameObjectManagerInrterface
		{
			static_assert(sizeof...(Args) > 0, "notting template Args");
			static_assert(MyTU::is_all_base_of_v<GameObject, Args...>, "is not base of Args");

			GameObjectManager() :max_index(0) {}
			~GameObjectManager() {}
		private:
			//GameObjectType�̍ő�T�C�Y���i�[���邽��.
			struct GameObjectBuffer {
				GameObject obj;
				std::byte buffer[MyTU::Sizeof<GameObject, Args...>::max - sizeof(GameObject)];
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

			//�Q�[���I�u�W�F�N�g�����܂�.
			template<typename T>
			GameObject* create_game_object() {
				static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
				new((void*)(&(mobjs[max_index]))) T();
				max_index++;
				return &(mobjs[max_index - 1].obj);
			}
		private:
			std::array<GameObjectBuffer, N> mobjs;
			std::size_t max_index;
			//�R���|�[�l���g�T�C�Y���s������Ȃ��H
			//Component</*Sean?*/> compornents[N];
		};

		template<class T, std::size_t N>
		struct polyObjct {
			std::array<T, N> arrayObj;
		};

		template<class T, std::size_t N>
		struct GameObjectPoly {

			std::array<T, N> arrayObj;
		};
	}
}
