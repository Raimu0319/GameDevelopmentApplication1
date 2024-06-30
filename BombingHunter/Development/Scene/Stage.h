#pragma once

#define D_PIVOT_CENTER		//座標の原点を画像の中心にする

class Stage 
{
private:
	int stage_image;			//背景画像
	int stage_sound;			//メインBGM

public:
	Stage();
	~Stage();

	void Initialize() ;		//初期化処理
	void Update();			//更新処理
	void Draw() const ;		//描画処理
	void Finalize() ;		//終了時処理
};
