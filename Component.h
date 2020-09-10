#pragma once
#include "GameObject.h"

//GameObject‚ª‚Â‚±‚Æ.
//ª‚Ç‚¤‚â‚Á‚ÄŒÄ‚Ño‚·‚¨‚Â‚à‚è‚Å?

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