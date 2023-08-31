#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
private:
	int x, y, w, h;
	int ImageX, ImageY, Image;
	int type = 0;
	int move = 0;
public:
	Stage();										// コンストラクタ
	Stage(float _x,float _y, int _image);		// 座標とサイズ指定
	~Stage();										// デストラクタ
	void Init(int type, int move);
	void Update();
	void Draw()const;								// 描画処理
	int GetImage();								// 画像読み込み
};