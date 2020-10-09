#pragma once
#include "GameObject.h"
#include "Component.h"
#include "TemplateUtil.h"
#include "Sprite.h"
#include <cstddef>
#include <algorithm>
#include <array>
#include <type_traits>

namespace MyGT {

	struct GameObjectManagerInrterface {
		virtual void start() = 0;
		virtual void update() = 0;
		// �R���|�[�l���g��ʔԍ����w��.
		//virtual void getComponent(int compornentID) = 0;
	};
	//�K�v�̂���R���|�\�l���g�����m��.
	//EXISTS�����܂����ƂƂ邢�����@�����邩������Ȃ����s���Ȃ̂�,
	//�ʂ̃e���v���[�g�N���X������Ă���.
	//�N�����@�������Ă�������.
	template <typename T,std::size_t N, bool EXISTS>
	struct ComponentArray_b {};
	template <std::size_t N>
	struct ComponentArray_b<SRC::Sprite,N,true> { std::array<Sprite, N> sprites; };
	template <typename T, std::size_t N,typename...Args>
	struct ComponentArray : public ComponentArray_b<T,N,MyTU::is_any_same_v<T, Args>> {};

	template <std::size_t N,typename...Args>
	struct GameObjectManagerHasComponentBase 
		: public GameObjectManagerInrterface,
		public ComponentArray<Sprite, N, Args...>
	{
		virtual void start() {}
		virtual void update(){}
		void getComponent() {

		}
		
	};
	//���S�������܂�l�����ĂȂ��̂Ŋ�Ȃ�����.
	//GameObject���p�����Ă�����̂��ő�T�C�Y�̃N���X�̑傫���ɂ��āA
	//�z��Ŋm��.
	//�R���|�[�l���g���g�p���Ȃ��ꍇ.
	template<std::size_t N,typename... Args >
	struct GameObjectManager 
		:public GameObjectManagerHasComponentBase<N,Args...>
//		:public GameObjectManagerInrterface
	{
		static_assert(sizeof...(Args) > 0, "notting template Args");
		static_assert(MyTU::is_all_base_of_v<GameObject,Args...>, "is not base of Args");

		GameObjectManager(const GameObjectManager&) = delete;
		GameObjectManager& operator=(const GameObjectManager&) = delete;
		GameObjectManager(GameObjectManager&&) = delete;
		GameObjectManager& operator=(GameObjectManager&&) = delete;

		GameObjectManager():max_index(0){}
		virtual ~GameObjectManager(){}
	private:
		//GameObjectType�̍ő�T�C�Y���i�[���邽��.
		struct GameObjectBuffer {
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
		GameObject* createGameObject() {
			static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
			new((void*)(&(mobjs[max_index]))) T();
			max_index++;
			return &(mobjs[max_index-1].obj);
		}
	private:
		std::array<GameObjectBuffer,N> mobjs;
		std::size_t max_index;
		//�R���|�[�l���g�T�C�Y���s������Ȃ��H
		//Component</*Sean?*/> compornents[N];
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
	namespace inc {
		//GameObject���R���|�[�l���g�������Ă���O��.
		template<std::size_t N, typename... Args >
		struct GameObjectManager :public GameObjectManagerInrterface
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
			GameObject* createGameObject() {
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
