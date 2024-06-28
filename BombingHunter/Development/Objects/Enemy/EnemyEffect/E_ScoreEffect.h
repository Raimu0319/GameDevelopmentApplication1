#pragma once
#include "../../GameObject.h"

class E_ScoreEffect : public GameObject
{
private:
	int animation_count;	//フレームカウント
	int toumeido;			//透明度を徐々に変化させる
	int	e_score_img[4];		//スコア画像
	Vector2D Direction;			//移動速度
	Vector2D start_location;	//初期座標

public:
	int image;				//画像
	int filp_flag;			//反転フラグ

public:
	E_ScoreEffect();
	~E_ScoreEffect();

	void Initialize();			//初期化処理
	void Update();				//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了時処理	

	void MoveScore();				//移動処理
	void SetScoreImage(int score);		//スコアの取得処理
private:
	void EraseAnim();			//スコアの削除処理
};
