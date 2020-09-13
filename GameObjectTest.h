#pragma once
#include "DxLib.h"
#include "GameObject.h"
#include "Sprite.h"

using namespace MyGT;
const char* test__ = "test";

struct GameObjectTest : public GameObject
{
	using GameObject::GameObject;
	GameObjectTest(){
		id = 1;
	}
	~GameObjectTest() {
		GraphResource<'s', 'a', 't', 'u', 'k', 'i', '.', 'p', 'n', 'g'>::DeleteG();
	}

	void start() {
		id = GraphResource<'s', 'a', 't', 'u', 'k', 'i', '.', 'p', 'n', 'g'>::LoadG();
	}
	void update() {
		DrawGraph(transform.position.x,transform.position.y,id,true);
		transform.position.x++;
		if (transform.position.x >= 640) {
			transform.position.x = 0;
		}
	}
};