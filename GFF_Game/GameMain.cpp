#include "GameMain.h"
GameMain::GameMain()
{
	player = new Player();
	ui = new UI();
	for (int i = 0; i < SCREEN_WIDTH / STAGE_SIZE; i++) {
		stage[i] = new Stage((STAGE_SIZE * i), SCREEN_HEIGHT - STAGE_SIZE, 0);
	}
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	player->Update();
	player->GroundFlg = false;
	ui->Update(player->GetMaxHP(),player->GetHP());

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
	ui->Draw();
	for (int i = 0; i < 63; i++) {
		if (stage[i] != nullptr) {
			stage[i]->Draw(player->GetCenterX(), player->GetCenterY());
		}
	}
}

void GameMain::Game()
{
}
