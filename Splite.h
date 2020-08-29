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
	///�e�q�֌W�ō쐬.
	constexpr void makeGameObject(GameObject * _gameObject)
	{

	};

public:
	virtual void start() {};
	virtual void update() {};

public:
	//�R���|�[�l���g�͊e�R���|�[�l���g���X�g���[�W�������Ă���.
	//�m�ێ��͂�����󂯎��
	std::vector<Component*> compornents;
	int id = 0;
	Sprite* parent = nullptr;
	Transform transform;
};

