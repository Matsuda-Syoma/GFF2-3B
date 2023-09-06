#pragma once
#include"DxLib.h"
#include"AbstractScene.h"
#include"Player.h"
#include"Stage.h"
#include"UI.h"
class GameMain : public AbstractScene
{
private:
	Player* player;
	Stage* stage[63];
	UI* ui;
public:
	GameMain();
	// �R���X�g���N�^
	~GameMain();								// �f�X�g���N�^

	virtual AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;					// �`��Ɋւ��邱�Ƃ�����
	void Game();								// �Q�[���̏���
};

