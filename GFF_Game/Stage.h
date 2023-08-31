#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
private:
	int x, y, w, h;
	int ImageX, ImageY, Image;
	int type = 0;
	int move = 0;
public:
	Stage();										// �R���X�g���N�^
	Stage(float _x,float _y, int _image);		// ���W�ƃT�C�Y�w��
	~Stage();										// �f�X�g���N�^
	void Init(int type, int move);
	void Update();
	void Draw()const;								// �`�揈��
	int GetImage();								// �摜�ǂݍ���
};