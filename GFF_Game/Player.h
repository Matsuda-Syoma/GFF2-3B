#pragma once
#include"DxLib.h"
#include"common.h"
#include"CharaBase.h"
#include"PAD_INPUT.h"
#include"Stage.h"
#include<math.h>

#define AFTIMGNUM 10

class Player : public CharaBase
{
private:
	float x, y;						// プレイヤーの座標
	float befx[AFTIMGNUM], befy[AFTIMGNUM],befalp[AFTIMGNUM];
	float w, h;						// プレイヤーの大きさ
	float speedX, speedY;			// プレイヤーの速度
	float speedXMax;
	float startX;
	float CursorX;
	float CursorY;
	int JumpHitDelay;
	static const int WIDTH = 48;
	static const int HEIGHT = 48;
	float CursorLockX;
	float CursorLockY;
	int DashCoolTime;
	struct SKILL
	{
		float Damage;

	};
public:

	bool GroundFlg;
	Player();
	~Player();
	void Update()override;
	void Draw()const override;
	bool IsGround(Stage box);
	float GetBoxSide(BoxCollider box, int i);
	int GetHP();
	int GetMaxHP();
	float inputLX();
	float inputRX();
	float inputRY();
};

