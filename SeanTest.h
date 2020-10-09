#pragma once
#include "Sean.h"
#include "GameObjectTest.h"
#include "GameObjectTest2.h"
#include "FpsObject.h"
#include "GameObjectManager.h"

static const std::size_t _TESTSIZE = 60000;

template<typename T>
using pl_vector = std::pmr::vector<T>;
using namespace MyGT;

struct SeanTest : public Sean<
	GameObjectManager<_TESTSIZE, GameObjectTest,GameObjectTest2>,
	GameObjectManager<5,GameObject>,
	GameObjectManager<1, FpsObject>>
{
	// 以下のように作ることでこのクラスの後ろに作られる。
	// ※ただしこのクラス自体が同じmemory_resouseを使用している前提.
	SeanTest(std::pmr::memory_resource* gallocator)
		: Sean(gallocator)
	{
		for (int i = 0; i < _TESTSIZE/2; i++) {
			createGameObject<GameObjectTest, 0>();
		}
		for (int i = 0; i < _TESTSIZE / 2; i++) {
			createGameObject<GameObjectTest2, 0>();
		}
		createGameObject<FpsObject, 2>();
	}
	virtual ~SeanTest()
	{
	}

};