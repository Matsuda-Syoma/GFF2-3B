#include "GameMain.h"
GameMain::GameMain()
{
	player = new Player();
	stage[0] = new Stage(0, 450, 640, 480, 0);
	stage[1] = new Stage(0, 250, 240, 30, 0);
	stage[2] = new Stage(340, 400, 40, 50, 0);
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	player->Update();
	player->GroundFlg = false;
	for (int i = 0; i < 63; i++) {
		if (stage[i] != nullptr) {
			stage[i]->Update();
			if (player->IsGround(*stage[i])) {
			}
		}
	}
	return this;
}

void GameMain::Draw() const
{
	player->Draw();
	for (int i = 0; i < 63; i++) {
		if (stage[i] != nullptr) {
			stage[i]->Draw();
		}
	}
}

void GameMain::Game()
{
}
