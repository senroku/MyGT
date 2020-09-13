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
	//安全性をあまり考慮してないので危ないかも.
	//GameObjectを継承しているものを最大サイズのクラスの大きさにして、
	//配列で確保.
	template<std::size_t N,typename... Args >
	struct GameObjectManager :public GameOvjectManagerInrterface
	{
		GameObjectManager():max_index(0){}
		~GameObjectManager(){}
	private:
		//GameObjectTypeの最大サイズを格納するため.
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
		//コンポーネントサイズが不明じゃない？
		//Component</*Sean?*/> compornents[N];
	};
}