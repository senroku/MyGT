#pragma once
#include "Sean.h"
#include "GameObjectTest.h"

template<typename T>
using pl_vector = std::pmr::vector<T>;

struct SeanTest : public Sean 
{
	// 以下のように作ることでこのクラスの後ろに作られる。
	// ※ただしこのクラス自体が同じmemory_resouseを使用している前提.
	SeanTest(std::pmr::memory_resource* gallocator)
		: Sean(gallocator)
		,objectsA(pl_vector<GameObjectTest>(0, gallocator))
		,objectsB(pl_vector<GameObject>(0, gallocator))
	{
		objectsA.resize(0);
		objectsB.resize(0);
	}
	virtual ~SeanTest()
	{
	}

	void start() {
		//vtableを使用際の方法
		memccpy(&(objectsA[0]), &GameObject(), 0, sizeof(GameObject));
		objectsA.resize(objectsA.size()+1);
		//objectsA[0] = *static_cast<GameObjectTest*>(&test);
	}

	void update(){
		for (size_t i = 0; i < objectsA.size(); i++) {
			//(&objectsA[i])->update();
			static_cast<GameObject*>(&objectsA[i])->update();
		}
		for (size_t i = 0; i < objectsB.size(); i++)
		{
			static_cast<GameObject*>(&objectsB[i])->update();
		}

	}

protected:
	template<typename T>
	constexpr GameObject* createGameObject() 
	{
		return objectsA.push_back(T);
	}
private:
	pl_vector<GameObjectTest> objectsA;
	pl_vector<GameObject> objectsB;
};

//ポインタ保持の場合.
//#pragma once
//#include "Sean.h"
//#include "GameObjectTest.h"
//
//template<typename T>
//using pl_vector = std::pmr::vector<T>;
//
//struct SeanTest : public Sean
//{
//	// 以下のように作ることでこのクラスの後ろに作られる。
//	// ※ただしこのクラス自体が同じmemory_resouseを使用している前提.
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
//		//vtableを使用際の方法
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
