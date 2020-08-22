#pragma once
#include "GameObject.h"


struct GameObjectTest : public GameObject
{
	GameObjectTest(){
		id = 1;
	}
	~GameObjectTest() {

	}

	void start() {

	}
	void update() {
		int i = 0;
		i++;
	}


};