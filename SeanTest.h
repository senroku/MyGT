#pragma once
#include "Sean.h"
#include "GameObjectTest.h"
#include "GraphFPS.h"
#include "GameObjectManager.h"

template<typename T>
using pl_vector = std::pmr::vector<T>;
using namespace MyGT;

struct SeanTest : public Sean 
{
	// �ȉ��̂悤�ɍ�邱�Ƃł��̃N���X�̌��ɍ����B
	// �����������̃N���X���̂�����memory_resouse���g�p���Ă���O��.
	SeanTest(std::pmr::memory_resource* gallocator)
		: Sean(gallocator)
	{
	}
	virtual ~SeanTest()
	{
	}

	void start() {
		createGameObject<GameObjectTest>();
		createGameObject<GameObjectTest>();
		createGameObject<GameObject>();
		//vtable�����鎞�_��vtable�Q�Ƃ��Ċ֐������ɍs��.
		createGameObject < GameObjectTest>();
		managerA.start();
	}

	void update(){
		//vtable�����鎞�_��vtable�Q�Ƃ��Ċ֐������ɍs��.
		managerA.update();
		_fps.update();
	}

protected:
	template<typename T>
	constexpr GameObject* createGameObject() 
	{
		static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
		GameObject* result = nullptr;

		//vtable���Ƃ��Ă͂�
		if constexpr (std::is_same_v<GameObjectTest,T>) {
			managerA.add<T>();
		}
		else if constexpr (std::is_same_v<GameObject,T>) {
			managerB.add<T>();
		}
		return result;
	}

private:
	fpsObject _fps;
	GameObjectManager<5, GameObjectTest> managerA;
	GameObjectManager<5> managerB;
};

//�|�C���^�ێ��̏ꍇ.
//#pragma once
//#include "Sean.h"
//#include "GameObjectTest.h"
//
//template<typename T>
//using pl_vector = std::pmr::vector<T>;
//
//struct SeanTest : public Sean
//{
//	// �ȉ��̂悤�ɍ�邱�Ƃł��̃N���X�̌��ɍ����B
//	// �����������̃N���X���̂�����memory_resouse���g�p���Ă���O��.
//	SeanTest(std::pmr::memory_resource* gallocator)
//		: Sean(gallocator)
//		, objectsA(new pl_vector<GameObjectTest>(10, gallocator))
//		, objectsB(new pl_vector<GameObject>(10, gallocator))
//	{
//		objectsA->resize(0);
//		objectsB->resize(0);
//	}
//	virtual ~SeanTest()
//	{
//	}
//
//	void start() {
//		//vtable���g�p�ۂ̕��@
//		//objectsA.push_back(*(GameObjectTest*)(&GameObject()));
//		//objectsA[0] = *static_cast<GameObjectTest*>(&test);
//	}
//
//	void update() {
//		for (size_t i = 0; i < objectsA->size(); i++) {
//			//(&objectsA[i])->update();
//			static_cast<GameObject*>(&(*objectsA)[i])->update();
//		}
//		for (size_t i = 0; i < objectsB->size(); i++)
//		{
//			static_cast<GameObject*>(&(*objectsB)[i])->update();
//		}
//
//	}
//
//protected:
//	template<typename T>
//	constexpr GameObject* createGameObject()
//	{
//		return objectsA.push_back(T);
//	}
//private:
//	pl_vector<GameObjectTest>* objectsA;
//	pl_vector<GameObject>* objectsB;
//};
