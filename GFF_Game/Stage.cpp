#include "DxLib.h"
#include "common.h"
#include "Stage.h"
Stage::Stage()
{
}


Stage::Stage(float _x, float _y, float _w, float _h, int _image)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	ImageX = box.left + (_w - _x) / 2;
	ImageY = box.top + (_h - _y) / 2;
	Image = _image;
}

Stage::~Stage()
{
}

void Stage::Init(int _type, int _move) {
	type = _type;
	move = _move;
}

void Stage::Update() {

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	if (type == 1) {
		y--;
	}
}

void Stage::Draw() const
{
	//DrawGraph(box.left, box.top, Image, true);
	DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, false);
	
}

int Stage::GetImage()
{
	return Image;
}
