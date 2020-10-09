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
		// コンポーネント種別番号を指定.
		//virtual void getComponent(int compornentID) = 0;
	};
	//必要のあるコンポ―ネントだけ確保.
	//EXISTSをうまいこととるいい方法があるかもしれないが不明なので,
	//別のテンプレートクラスを作っている.
	//誰か方法を教えてください.
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
	//安全性をあまり考慮してないので危ないかも.
	//GameObjectを継承しているものを最大サイズのクラスの大きさにして、
	//配列で確保.
	//コンポーネントを使用しない場合.
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
		//GameObjectTypeの最大サイズを格納するため.
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

		//ゲームオブジェクトを入れます.
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
		//コンポーネントサイズが不明じゃない？
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
		//GameObjectがコンポーネントを持っている前提.
		template<std::size_t N, typename... Args >
		struct GameObjectManager :public GameObjectManagerInrterface
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
			GameObject* createGameObject() {
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
