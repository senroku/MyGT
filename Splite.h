#pragma once
#include "GameObject.h"

struct Sprite :public GameObject {
	Sprite() = default;

	Sprite(Sprite* _gameobject)
		:transform(_gameobject->transform), parent(nullptr) {
	}

	Sprite(Transform _transform)
		:parent(nullptr), transform(_transform) {}

	virtual ~Sprite() {};

private:
	///親子関係で作成.
	constexpr void makeGameObject(GameObject * _gameObject)
	{

	};

public:
	virtual void start() {};
	virtual void update() {};

public:
	//コンポーネントは各コンポーネントがストレージを持っている.
	//確保時はそれを受け取る
	std::vector<Component*> compornents;
	int id = 0;
	Sprite* parent = nullptr;
	Transform transform;
};

