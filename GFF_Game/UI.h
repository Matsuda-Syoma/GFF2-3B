#pragma once
#include "common.h"
#include "DxLib.h"
class UI
{
private:
	int HP;
	int MaxHP;
	int Score;
	int Skill_1;
	int Skill_2;
public:
	UI();
	~UI();
	void Update(int _mhp, int _hp);
	void Draw()const;
};

