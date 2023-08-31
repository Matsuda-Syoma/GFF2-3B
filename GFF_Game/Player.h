#pragma once
#include"DxLib.h"
#include"common.h"
#include"BoxCollider.h"
#include"PAD_INPUT.h"
#include"Stage.h"
#include<math.h>
class Player : public BoxCollider
{
private:
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	float speedX, speedY;			// �v���C���[�̑��x
	float speedXMax;
	float startX;
	static const int WIDTH = 32;
	static const int HEIGHT = 48;
public:

	bool GroundFlg;
	Player();
	~Player();
	void Update();
	void Draw()const;
	bool IsGround(Stage box);
	float GetBoxSide(BoxCollider box, int i);
	float inputX();
};
