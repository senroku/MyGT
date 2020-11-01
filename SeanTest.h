#pragma once
#include "Sean.h"
#include "GameObjectTest.h"
#include "GameObjectTest2.h"
#include "FpsObject.h"
#include "GameObjectManager.h"
#include "Utils.h"

static const std::size_t _TESTSIZE = 60000;

template<typename T>
using pl_vector = std::pmr::vector<T>;
using namespace MyGT;

//�p�����Ⴀ����́H
//�Ⴂ������Ȃ�����Ƃ肠��������.
using GameObjcts = GameObjectManager<5, GameObject>;
using GameObjectTests = GameObjectManager<_TESTSIZE, GameObjectTest, GameObjectTest2>;

struct SeanTest 
	: public Sean<GameObjectTests,GameObjcts,FpsManager>
{
	// �ȉ��̂悤�ɍ�邱�Ƃł��̃N���X�̌��ɍ����B
	// �����������̃N���X���̂�����memory_resouse���g�p���Ă���O��.
	SeanTest(std::pmr::memory_resource* gallocator)
		: Sean(gallocator)
	{
		for (int i = 0; i < _TESTSIZE/2; i++) {
			create_game_object<GameObjectTest, GameObjectTests>();
		}
		for (int i = 0; i < _TESTSIZE / 2; i++) {
			create_game_object<GameObjectTest2, GameObjectTests>();
		}
		//SeanManager::get_instance()->create_game_object<FpsObject, FpsManager>();
		//Instantiate<FpsObject, FpsManager>();
		create_game_object<FpsObject, FpsManager>();
	}
	virtual ~SeanTest()
	{
	}

};