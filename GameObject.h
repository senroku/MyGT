#pragma once

#include "Transform.h"
#include "Component.h"
#include <vector>

struct GameObject 
{
	GameObject() = default;

	GameObject(GameObject* _gameobject)
		:transform(_gameobject->transform), parent(nullptr) {
	}

	GameObject(Transform _transform)
		:parent(nullptr),transform(_transform) {}

	virtual ~GameObject() {};

private:
	///親子関係で作成.
	constexpr void makeGameObject(GameObject* _gameObject) 
	{

	};

public:
	virtual void start() {};
	virtual void update() {};

public:
	GameObject* parent = nullptr;
	Transform transform;
	int id = 0;
	//コンポーネントは各コンポーネントがストレージを持っている.
	//確保時はそれを受け取る
	std::vector<Component*> compornents;
};