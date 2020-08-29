#pragma once
#include "GameObject.h"

//GameObject‚ª‚Â‚±‚Æ.
struct Component
{
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(Component&&) = delete;

private:
	Component() = default;

public:
	~Component() {};

	Component(GameObject* obj) {
		object = obj;
	}

	virtual void start() {};
	virtual void update() {};

protected:
	GameObject* object;
};
