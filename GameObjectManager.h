#pragma once
#include "GameObject.h"
#include "Component.h"
#include <cstddef>
#include <algorithm>
#include <variant>

namespace MyGT {
	template<std::size_t N,typename... Args >
	struct GameObjectManager {
		void start() {
			for (int i=0;i<N;i++)
				(GameObject)mobjs.start();
		}
		void update() {
			for (int i = 0; i < N; i++)
				(GameObject)mobjs.updatet();

		}
	private:
		std::variant<GameObject, Args> mobjs[N];
		//コンポーネントサイズが不明じゃない？
		Component</*Sean?*/> compornents[N];
	};
}