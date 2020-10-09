#pragma once
#include "GameObject.h"

//GameObjectが持つこと.
//↑どうやって呼び出すおつもりで?

namespace MyGT {
	struct GameObject;
	struct Component
	{
		Component() = default;
		Component(GameObject* obj) {
			object = obj;
		}
	public:
		virtual ~Component() {};

		virtual void start() {};
		virtual void update() {};

	protected:
		GameObject* object;
	};
}