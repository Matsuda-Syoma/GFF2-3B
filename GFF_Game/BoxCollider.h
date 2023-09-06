#pragma once

typedef struct Box {
	float top;
	float bottom;
	float left;
	float right;
} Box;

class BoxCollider
{
private:

protected:
	Box box; // �����蔻��

public:
	char name;
	BoxCollider();
	void GetSize(float& top, float& bottom, float& left, float& right);
	int HitBox(BoxCollider boxCollider) const;								// ��A���A�E�A��
	void DrawCollider() const;
	// 1:��2:��3:��4:�E
	float GetSide(int i);
	float GetCenterX();
	float GetCenterY();
};

