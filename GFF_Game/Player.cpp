#include "Player.h"

Player::Player()
{
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
}

Player::~Player()
{
}

void Player::Update()
{
	// �v���C���[�̉摜�̒��S���W
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
	if (fabsf(inputRX()) > 0.3 || fabsf(inputRY()) > 0.3) {
		CursorX = x + (w / 2) + inputRX() * 100;
		CursorY = y + (h / 2) + inputRY() * 100;
	}

	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_RIGHT_SHOULDER)) {
		speedX = (CursorX - (x + (w / 2))) * 5;
		speedY = (CursorY - (y + (h / 2))) * 5 + -100;
		JumpHitDelay = 3;
	}

	// �E����
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

	// ������
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
	printfDx("%f", speedX);

	// �v���C���[�̍��W�X�V
	x += speedX / FRAMERATE;
	y += speedY / FRAMERATE;
}

void Player::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom, 0xff0000, 1);
	DrawCircle(CursorX, CursorY, 3, 0xffffff, 0);
}

// �R���g���[���̓��͂�Ԃ�
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
	// �㑤�ɓ��������Ƃ��̔���
	if (HitStage == 1) {

		GroundFlg = true;
		if (JumpHitDelay <= 3 - 2) {
			speedY = 0;
			y = GetBoxSide(box, 1) - h;
		}

		return true;
	}

	// �����ɂ����������̔���
	if (HitStage == 2) {
		//y = GetBoxSide(box, 2) - (y - GetBoxSide(box, 2));
		speedX = 0;
		y = GetBoxSide(box, 2) + 1;
		return true;
	}
	// ���ɂ����������̔���
	if (HitStage == 3) {
		speedX = 0;
		x = GetBoxSide(box, 3) - (w + 1);
		return true;
	}
	// �E�ɂ����������̔���
	if (HitStage == 4) {
		//x = GetBoxSide(box, 4) - (x - GetBoxSide(box, 4));
		x = GetBoxSide(box, 4) + 1;
		return true;
	}
	return false;
}

// �����Ő��l��Ԃ�(1:��A2:���A3:���A4:�E)
float Player::GetBoxSide(BoxCollider box, int i) {
	return box.GetSide(i);
}