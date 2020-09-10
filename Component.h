#pragma once
#include "GameObject.h"

//GameObjectが持つこと.
//↑どうやって呼び出すおつもりで?

namespace MyGT {
	class GameObject;
	struct Component
	{
		Component() = default;
		Component(GameObject* obj) {
			object = obj;
		}
	public:
		~Component() {};

		virtual void start() {};
		virtual void update() {};

	protected:
		GameObject* object;
	};
}