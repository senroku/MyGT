#pragma once

#include "DxLib.h"
#include "Transform.h"
#include "Component.h"
#include "LoadgrphMacro.h"
#include <vector>

namespace MyGT {
	struct Component;
	struct GameObject
	{
		GameObject() = default;

		GameObject(GameObject* _gameobject)
			:transform(_gameobject->transform), parent(nullptr) {
		}

		GameObject(Transform _transform)
			:parent(nullptr), transform(_transform) {}

		virtual ~GameObject() {};

	protected:
		///�e�q�֌W�ō쐬.
		constexpr void makeGameObject(GameObject* _gameObject)
		{
		};


	public:
		virtual void start() {
			//id = GraphResource<'t', 'e', 's', 't', '4', '.', 'b', 'm', 'p'>::LoadG();
			id = GraphResource<"test4.bmp">::LoadG();
		};
		virtual void update() {
			DrawGraph(300, 10, id, true);
		};

	public:
		//�R���|�[�l���g�͊e�R���|�[�l���g���X�g���[�W�������Ă���.
		//�m�ێ��͂�����󂯎��.
		std::vector<Component*>* compornents;
		int id = 0;
		GameObject* parent = nullptr;
		Transform transform;
	};
}
