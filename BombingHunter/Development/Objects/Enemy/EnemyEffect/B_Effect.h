#pragma once
#include "../../GameObject.h"

class B_Effect : public GameObject
{
private:
	int animation_count;	//フレームカウント
	int toumeido;			//透明度を徐々に変化させる
	int	b_eff_img[3];		//テキ弾画像

public:
	int image;				//画像
	int filp_flag;			//反転フラグ

public:
	B_Effect();
	~B_Effect();

	void Initialize();			//初期化処理
	void Update();				//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了時処理	
private:
	void AnimControl();			//アニメーション処理
};
