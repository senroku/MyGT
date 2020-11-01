#pragma once
#include "DxLib.h"
#include "GameObject.h"
#include "Sprite.h"

using namespace MyGT;
#define GameObjectTestStr "ammo2.bmp"

struct GameObjectTest2 : public GameObject
{
	using GameObject::GameObject;
	GameObjectTest2() {
		id = 1;
	}
	~GameObjectTest2() {
		GraphResource<GameObjectTestStr>::delete_graph();
	}

	void start() {
		id = GraphResource<GameObjectTestStr>::load_graph();
		transform.position.y = 240;
	}
	void update() {
		DrawGraph(transform.position.x, transform.position.y, id, true);
		transform.position.x++;
		if (transform.position.x >= 640) {
			transform.position.x = -320;
		}
	}
};