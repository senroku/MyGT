#pragma once
#include "DxLib.h"
#include "GameObject.h"
#include "Sprite.h"

#define GameObjectTestStr "ammo.bmp"
//#define GameObjectTestStr "satuki.png"

using namespace MyGT;


struct GameObjectTest : public GameObject
{
	using GameObject::GameObject;
	GameObjectTest(){
		id = 1;
	}
	~GameObjectTest() {
		GraphResource<GameObjectTestStr>::DeleteG();
	}

	void start() {
		id = GraphResource<GameObjectTestStr>::LoadG();
	}
	void update() {
		DrawGraph(transform.position.x,transform.position.y,id,true);
		transform.position.x++;
		if (transform.position.x >= 640) {
			transform.position.x = -320;
		}
	}
};