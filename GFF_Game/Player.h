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
	float x, y;					// プレイヤーの座標
	float w, h;					// プレイヤーの大きさ
	float speedX, speedY;			// プレイヤーの速度
	float speedXMax;
	float startX;
	float CursorX;
	float CursorY;
	int JumpHitDelay;
	static const int WIDTH = 48;
	static const int HEIGHT = 48;
public:

	bool GroundFlg;
	Player();
	~Player();
	void Update();
	void Draw()const;
	bool IsGround(Stage box);
	float GetBoxSide(BoxCollider box, int i);
	float inputLX();
	float inputRX();
	float inputRY();
};

