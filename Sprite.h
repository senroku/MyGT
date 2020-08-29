#pragma once

#include "Component.h"
#include "DxLib.h"
#include <map>

constexpr int id_max = 1000;

//íxÇ¢
struct Sprite : public Component {
private:
	Sprite() = default;
public:
	~Sprite(){}

	void start() {
		position = &(object->transform.position);
	}
	void update() {
		DrawGraph(position->x,position->y, id,true);
	}

private:
	//idä«óù
	static std::map<int,int> ids[id_max];

private:
	int id;
	Vec2* position;
};