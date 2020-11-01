#pragma once

#include "DxLib.h"
#include "Transform.h"
#include "Component.h"
#include "LoadgrphMacro.h"
#include "SeanManager.h"
#include <vector>
#include <concepts>

namespace MyGT {
	struct Component;

	namespace PrivateSpace {
		struct GameObjectAbstruct {
			GameObjectAbstruct() = default;

			GameObjectAbstruct(GameObjectAbstruct* _gameobject)
				:transform(_gameobject->transform), parent(nullptr) {
			}

			GameObjectAbstruct(Transform _transform)
				:parent(nullptr), transform(_transform) {}

			virtual ~GameObjectAbstruct() {};

		public:
			//template<typename T, std::size_t N = -1>
			//T* create_game_object() {
			//	return SeanManager::get_instance().create_game_object<T,N>();
			//}

		public:
			virtual void start() {};
			virtual void update() {};

		public:
			int id = 0;
			GameObjectAbstruct* parent = nullptr;
			Transform transform;
		};

	}


	struct GameObject : public PrivateSpace::GameObjectAbstruct
	{
		GameObject() = default;
		GameObject(GameObject* _gameobject)
			:PrivateSpace::GameObjectAbstruct(_gameobject){
		}

		GameObject(Transform _transform)
			:PrivateSpace::GameObjectAbstruct(_transform){}

		virtual ~GameObject() {};


	public:
		virtual void start() {
		};
		virtual void update() {
		};
	};

	//未実装
	//コンポーネントがGameObject内で管理されているパターン.
	namespace inc {
		struct GameObject : public PrivateSpace::GameObjectAbstruct
		{
			GameObject() = default;
			GameObject(GameObject* _gameobject)
				:PrivateSpace::GameObjectAbstruct(_gameobject) {
			}

			GameObject(Transform _transform)
				:PrivateSpace::GameObjectAbstruct(_transform) {}

			virtual ~GameObject() {};


		public:
			virtual void start() {
			};
			virtual void update() {
			};
		public:
			//ここをどうするかが不明.
			std::array<Component*, 10> components;
		};

	}
}
