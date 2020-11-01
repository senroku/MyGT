#pragma once

#include "Component.h"
#include "Sprite.h"
#include "EBO.h"


namespace MyGT {

	//必要のあるコンポ―ネントだけ確保.
//EXISTSをうまいこととるいい方法があるかもしれないが不明なので,
//別のテンプレートクラスを作っている.
//誰か方法を教えてください.
	template <typename T, std::size_t N, bool EXISTS>
	struct ComponentArray_base {
		//多重継承予定だから関数はまずい.
		//template<typename T>constexpr bool EXIST() { return EXIST; }
		virtual ~ComponentArray_base() {}
	};

	template <typename T, std::size_t N, typename...Args>
	struct ComponentArray : public ComponentArray_base<T, N, MyTU::is_any_base_of_v<T, Args...>> {};


	//所持があった場合GameObjectManagerのCompnentｓへ追加するため.
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
		//コンポーネントはUpdateGOのアップデート後にまとめて処理.
		void update() {
			if constexpr (isSprites) {
				void* p = &(this->sprites);
			}
			//else if constexpr ()
			//else
		}
	};

}