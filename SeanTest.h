#pragma once
#include "Sean.h"
#include "GameObjectTest.h"
#include "GraphFPS.h"

template<typename T>
using pl_vector = std::pmr::vector<T>;
using namespace MyGT;

struct SeanTest : public Sean 
{
	// 以下のように作ることでこのクラスの後ろに作られる。
	// ※ただしこのクラス自体が同じmemory_resouseを使用している前提.
	SeanTest(std::pmr::memory_resource* gallocator)
		: Sean(gallocator)
		,objectsA(pl_vector<GameObjectTest>(10, gallocator))
		,objectsB(pl_vector<GameObject>(10, gallocator))
	{
		objectsA.resize(0);
		objectsB.resize(0);
	}
	virtual ~SeanTest()
	{
	}

	void start() {
		createGameObject<GameObjectTest>();
		createGameObject<GameObjectTest>();
		createGameObject<GameObject>();
		//vtableがある時点でvtable参照して関数を見に行く.
		for (int i = 0; i < objectsA.size(); i++) {
			objectsA[i].start();
		}
		for (int i = 0; i < objectsB.size(); i++) {
			objectsB[i].start();
		}
	}

	void update(){
		//vtableがある時点でvtable参照して関数を見に行く.
		for (int i = 0; i < objectsA.size();i++) {
			objectsA[i].update();
		}
		//for (int i = 0; i < objectsB.size();i++) {
		//	objectsB[i].update();
		//}
		_fps.update();
	}

protected:
	template<typename T>
	constexpr GameObject* createGameObject() 
	{
		static_assert(std::is_base_of_v<GameObject, T>, "T is not Sean extended interface class");
		GameObject* result = nullptr;

		//vtableごとあてはめ
		if constexpr (std::is_same_v<GameObjectTest,T>) {
			objectsA.resize(objectsA.size() + 1);
			result = new((void*)(&objectsA.back())) T();
		}
		else if constexpr (std::is_same_v<GameObject,T>) {
			objectsB.resize(objectsB.size() + 1);
			result = new((void*)(&objectsB.back())) T();
		}
		return result;
	}

private:
	fpsObject _fps;
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
