#include "Player.h"
#include "UI.h"

Player::Player()
{
	MaxHP = 100;
	HP = MaxHP;
	x = 40;
	y = 40 - HEIGHT;
	w = WIDTH;
	h = HEIGHT;
	speedX = 0;
	speedY = 0;
	speedXMax = 300.0f;
	startX = 15.0f;
	JumpHitDelay = 0;
	GroundFlg = false;
	DashCoolTime = 0;
	for (int i = 0; i < AFTIMGNUM; i++) {
		befx[i] = 0;
		befy[i] = 0;
		befalp[i] = 0;
	}
}

Player::~Player()
{
}

void Player::Update()
{
	// プレイヤーの画像の中心座標
	/*imageX = x + (w / 2);
	imageY = y + (w / 2);*/

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	if (speedY < 800 && !GroundFlg) {
		speedY += 16.0f;
	}

	// jump

	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_B)) {
		speedY = 400.0f;
	}

	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A)) {
		if (GroundFlg) {
			speedY += -500.0f;
			JumpHitDelay = 3;
		}
	}

	if (JumpHitDelay > 0) {
		JumpHitDelay--;
	}
	if (DashCoolTime > 0) {
		speedX = CursorLockX;
		speedY = CursorLockY;

		befx[0] = x;
		befy[0] = y;

		for (int i = AFTIMGNUM - 1; i > 0; i--) {
			befx[i] = befx[i - 1];
			befy[i] = befy[i - 1];
			befalp[i] = 16;
		}
		if (DashCoolTime == 1) {
			speedX /= 16;
			speedY /= 16;
		}
		DashCoolTime--;
	}

	for (int i = 0; i < AFTIMGNUM; i++) {
		if (befalp[i] > 0) {
			befalp[i]--;
		}
	}

	if (fabsf(inputRX()) > 0.3 || fabsf(inputRY()) > 0.3) {
		CursorX = x + (w / 2) + inputRX() * 100;
		CursorY = y + (h / 2) + inputRY() * 100;
	}
	else {
		CursorX = x + (w / 2);
		CursorY = y + (h / 2);
	}
	// 風切り
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_RIGHT_SHOULDER) && DashCoolTime <= 0) {
		CursorLockX = (CursorX - (x + (w / 2))) * 20;
		CursorLockY = (CursorY - (y + (h / 2))) * 20 + -100;
		JumpHitDelay = 3;
		DashCoolTime = 10;
		for (int i = 0; i < AFTIMGNUM; i++) {
			befx[i] = 0;
			befy[i] = 0;
			befalp[i] = 0;
		}
	}

	//debug///////////////
	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_LEFT_SHOULDER) && HP > 0) {
		HP--;
	}

	// 右入力
	if (inputLX() >= 0.3) {
		//imageReverse = true;
		if (speedX < speedXMax) {
			//state = STATE::walk;
			speedX += startX;
		}
	}
	else if (inputLX() == 0 && speedX > 0 && GroundFlg) {
		//state = STATE::stay;
		speedX += -startX * 2;
	}

	// 左入力
	if (inputLX() <= -0.3) {
		//imageReverse = false;
		if (speedX > -speedXMax) {
			//state = STATE::walk;
			speedX += -startX;
		}
	}
	else if (fabsf(inputLX()) < 0.3 && speedX < 0 && GroundFlg) {
		//state = STATE::stay;
		speedX += startX * 2;
	}
	if (fabsf(inputLX()) < 0.3 && GroundFlg && JumpHitDelay <= 3 - 2) {
		speedX *= 0.7f;
		if (speedX < 0.15f && speedX > -0.15f) {
			speedX = 0;
		}
		//state = STATE::stay;
	}

	clsDx();
	printfDx("%d", DashCoolTime);

	// プレイヤーの座標更新
	x += speedX / FRAMERATE;
	y += speedY / FRAMERATE;
}

void Player::Draw() const
{
	for (int i = AFTIMGNUM - 1; i >= 0; i--) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64 * befalp[i]);
		DrawBox(befx[i], befy[i], befx[i] + WIDTH, befy[i] + HEIGHT,0xee0000,true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(box.left, box.top, box.right, box.bottom, 0xff0000, 1);
	//DrawBox(((SCREEN_WIDTH - WIDTH) / 2), ((SCREEN_HEIGHT - HEIGHT) / 2), ((SCREEN_WIDTH - WIDTH) / 2) + WIDTH, ((SCREEN_HEIGHT - HEIGHT) / 2) + HEIGHT, 0xff0000, 1);
	DrawCircle(CursorX, CursorY, 3, 0xffffff, 0);
}

// コントローラの入力を返す
float Player::inputLX() {
	return round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
}

float Player::inputRX() {
	return round(((float)PAD_INPUT::GetPadThumbRX() / 32767) * 1000) / 1000;
}

float Player::inputRY() {
	return round(((float)PAD_INPUT::GetPadThumbRY() / 32767) * 1000) / 1000;
}

bool Player::IsGround(Stage box) {

	int HitStage = Player::HitBox(box);
	// 上側に当たったときの判定
	if (HitStage == 1) {

		GroundFlg = true;
		if (JumpHitDelay <= 3 - 2) {
			speedY = 0;
			y = GetBoxSide(box, 1) - h;
		}

		return true;
	}

	// 下側にあたった時の判定
	if (HitStage == 2) {
		//y = GetBoxSide(box, 2) - (y - GetBoxSide(box, 2));
		speedX = 0;
		y = GetBoxSide(box, 2) + 1;
		return true;
	}
	// 左にあたった時の判定
	if (HitStage == 3) {
		speedX = 0;
		x = GetBoxSide(box, 3) - (w + 1);
		return true;
	}
	// 右にあたった時の判定
	if (HitStage == 4) {
		//x = GetBoxSide(box, 4) - (x - GetBoxSide(box, 4));
		x = GetBoxSide(box, 4) + 1;
		return true;
	}
	return false;
}

// 引数で数値を返す(1:上、2:下、3:左、4:右)
float Player::GetBoxSide(BoxCollider box, int i) {
	return box.GetSide(i);
}

int Player::GetHP() {
	return HP;
}

int Player::GetMaxHP() {
	return MaxHP;
}