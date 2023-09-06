#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Update(int _mhp, int _hp)
{
	MaxHP = _mhp;
	HP = _hp;
}

void UI::Draw() const
{
	DrawBox(20, 20, 500, 70, 0xffffff, true);
	DrawBox(20 + 3, 20 + 3, (20 + 3) + (500 - (23 + 3)) * ((float)HP / (float)MaxHP), 70 - 3, 0xff8888, true);
}
