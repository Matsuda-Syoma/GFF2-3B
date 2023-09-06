#pragma once
#include "BoxCollider.h"
class CharaBase : public BoxCollider
{
protected:
	int MaxHP = 1;
	int HP = MaxHP;
public:
	virtual void Update() = 0;
	virtual void Draw() const = 0;
};

