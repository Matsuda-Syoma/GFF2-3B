#include "BoxCollider.h"
#include <math.h>
#include "DxLib.h"
#include <vector>
BoxCollider::BoxCollider() {

}

// Box�̑傫����Get
void BoxCollider::GetSize(float& _top, float& _bottom, float& _left, float& _right) {
	_top = box.top;
	_bottom = box.bottom;
	_left = box.left;
	_right = box.right;
}

// Box���m���������Ă����False���A��
int BoxCollider::HitBox(BoxCollider boxCollider) const {
	Box other;			// ����̔���
	boxCollider.GetSize(other.top, other.bottom, other.left, other.right);
	float epsilon = 40.0f;		// �덷
	if (other.bottom < box.top) {
		return 0;
	}
	if (other.top > box.bottom) {
		return 0;
	}
	if (other.right < box.left) {
		return 0;
	}
	if (other.left > box.right) {
		return 0;
	}
	if (fabsf(box.bottom - other.top) < epsilon / 2) {	// ��ɓ��������Ƃ�1��Ԃ�
		return 1;
	}
	if (fabsf(box.right - other.left) < epsilon) {	// ���ɓ��������Ƃ�3��Ԃ�
		return 3;
	}
	if (fabsf(box.left - other.right) < epsilon) {	// �E�ɓ��������Ƃ�4��Ԃ�
		return 4;
	}
	if (fabsf(box.top - other.bottom) < epsilon) {	// ���ɓ��������Ƃ�2��Ԃ�
		return 2;
	}



	//if (box.bottom < other.top) {
	//	return 1;						// ��
	//}
	//if (other.bottom < box.top) {
	//	return 2;						// ��
	//}
	//if (box.right < other.left) {
	//	return 3;
	//}
	//if (other.right < box.left) {
	//	return 4;
	//}

	return 0;
}

//// ��`A�̉E�[����`B�̍��[�������ɂ���ꍇ
//if (rectangleA.x + rectangleA.width < rectangleB.x) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// ��`A�̍��[����`B�̉E�[�����E�ɂ���ꍇ
//if (rectangleA.x > rectangleB.x + rectangleB.width) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// ��`A�̉��[����`B�̏�[������ɂ���ꍇ
//if (rectangleA.y + rectangleA.height < rectangleB.y) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// ��`A�̏�[����`B�̉��[�������ɂ���ꍇ
//if (rectangleA.y > rectangleB.y + rectangleB.height) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// �d�Ȃ��Ă���ꍇ�A�ǂ̕����ɏd�Ȃ��Ă��邩�𔻒肷��
//if (rectangleA.x + rectangleA.width == rectangleB.x) {
//	return CollisionDirection::Right;		�E
//}
//
//if (rectangleA.x == rectangleB.x + rectangleB.width) {
//	return CollisionDirection::Left;		��
//}
//
//if (rectangleA.y + rectangleA.height == rectangleB.y) {
//	return CollisionDirection::Bottom;		��
//}
//
//if (rectangleA.y == rectangleB.y + rectangleB.height) {
//	return CollisionDirection::Top;			��
//}
//
//return CollisionDirection::None;
//}


void BoxCollider::DrawCollider() const {
	DrawBox(box.left, box.top, box.right, box.bottom, 0xFF, TRUE);
}

float BoxCollider::GetSide(int i) // 1:��2:��3:��4:�E
{
	switch (i)
	{
	case 1:
		return box.top;
		break;

	case 2:
		return box.bottom;
		break;

	case 3:
		return box.left;
		break;

	case 4:
		return box.right;
		break;

	default:
		return 0;
	}

}

float BoxCollider::GetCenterY() {
	return box.top - (box.bottom - box.top) / 2;
}