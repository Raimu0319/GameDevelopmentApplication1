#pragma once

#include "GameObject.h"
#include"../Scene/Scene.h"

class CreateClass: public GameObject
{
public:
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		return scene->CreateObject<T>(location);
	}
};