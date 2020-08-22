#pragma once
#include "Sean.h"
#include "GameObjectTest.h"

struct SeanTest : public Sean 
{
	// �ȉ��̂悤�ɍ�邱�Ƃł��̃N���X�̌��ɍ����B
	// �����������̃N���X���̂�����memory_resouse���g�p���Ă���O��.
	SeanTest(std::pmr::memory_resource* gallocator)
		: Sean(gallocator)
		,objectsA(std::pmr::vector<GameObjectTest>(10, gallocator))
		,objectsB(std::pmr::vector<GameObject>(10, gallocator))
	{
		objectsA.resize(0);
		objectsB.resize(0);
	}
	virtual ~SeanTest()
	{
	}

	void start() {
		GameObject test;
		objectsA.push_back(*static_cast<GameObjectTest*>(&test));
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
	GameObject* createGameObject() 
	{
		return objectsA.push_back(T);
	}
private:
	std::pmr::vector<GameObjectTest> objectsA;
	std::pmr::vector<GameObject> objectsB;
};
