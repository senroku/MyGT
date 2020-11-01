#pragma once
#include "GameObject.h"
#include "TemplateUtil.h"

//GameObject��������.
//���ǂ�����ČĂяo���������?

namespace MyGT {




	struct GameObject;
	struct Component
	{
		Component() = default;
		Component(GameObject* obj) {
			object = obj;
		}
		virtual ~Component() {};

		virtual void start() {};
		virtual void update() {};

	protected:
		GameObject* object;
	};
}