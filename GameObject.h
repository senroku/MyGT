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
	///�e�q�֌W�ō쐬.
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
	//�R���|�[�l���g�͊e�R���|�[�l���g���X�g���[�W�������Ă���.
	//�m�ێ��͂�����󂯎��
	std::vector<Component*> compornents;
};