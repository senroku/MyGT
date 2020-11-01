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
			// コンポーネント種別番号を指定.
			//virtual void getComponent(int compornentID) = 0;
		};
	}



	//安全性をあまり考慮してないので危ないかも.
	//GameObjectを継承しているものを最大サイズのクラスの大きさにして、
	//配列で確保.
	//コンポーネントを使用しない場合.
	// GameObjectManagerInrterfaceがなぜかサイズを持っている？<-vptrをお忘れか？.
	template<std::size_t N,typename... Args >
	struct EMPTY_BASES  GameObjectManager
		:public PrivateSpace::GameObjectManagerInrterface
		,public ComponentManager<N,Args...>	{
		static_assert(sizeof...(Args) > 0, "notting template Args");
		static_assert(MyTU::is_all_base_of_v<GameObject,Args...>, "is not base of Args");

		GameObjectManager():max_index(0){}
		virtual ~GameObjectManager(){}
	private:
		//GameObjectTypeの最大サイズを格納するため.
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

		//ゲームオブジェクトを入れます.
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
	//未実装.
	namespace inc {
		//GameObjectがコンポーネントを持っている前提.
		template<std::size_t N, typename... Args >
		struct GameObjectManager :public PrivateSpace::GameObjectManagerInrterface
		{
			static_assert(sizeof...(Args) > 0, "notting template Args");
			static_assert(MyTU::is_all_base_of_v<GameObject, Args...>, "is not base of Args");

			GameObjectManager() :max_index(0) {}
			~GameObjectManager() {}
		private:
			//GameObjectTypeの最大サイズを格納するため.
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

			//ゲームオブジェクトを入れます.
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
			//コンポーネントサイズが不明じゃない？
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
