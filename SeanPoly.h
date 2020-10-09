#pragma once
#include <memory>
#include <memory_resource>
#include <vector>
#include <string>
#include "Sean.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SeanManager.h"
//#include "GameObjectAllocator.h"



namespace MyGT {

	//PolyCollection‚ÌBase_Collection •—.
	template<class T, std::size_t N>
	struct SeanPoly :public SeanInterface {

	};
	
	void start(){}
	void update() {
		for (auto gmanger : m_p_gameManager) {
			gmanger->update();
		}
	}

}