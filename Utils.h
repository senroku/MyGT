#pragma once
#include <concepts>
#include "SeanManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"


namespace MyGT {

	//現在稼働しているGameObjectManager（usingでGameObjectManagerになっているもの）.
	//へGameObjectを追加する処理
	template<typename T, std::size_t N = -1>
	constexpr T* Instantiate() {
		return SeanManager::get_instance().create_game_object<T, N>();
	}
	template<typename T, typename GOM>
	requires std::derived_from<GOM, PrivateSpace::GameObjectManagerInrterface>
	constexpr T* Instantiate() {
		return SeanManager::get_instance().create_game_object<T, GOM>();
	}

}


