#include "E_ScoreEffect.h"
#include "DxLib.h"

E_ScoreEffect::E_ScoreEffect() : animation_count(0), filp_flag(0),image(NULL),toumeido(255)
{
	e_score_img[0] = NULL;
	e_score_img[1] = NULL;
	e_score_img[2] = NULL;
	e_score_img[3] = NULL;
}

E_ScoreEffect::~E_ScoreEffect()
{

}

//初期化処理
void E_ScoreEffect::Initialize()
{
	//画像の読み込み
	e_score_img[0] = LoadGraph("Resource/Images/Evaluation/Score_Hako.png");
	e_score_img[1] = LoadGraph("Resource/Images/Evaluation/Score_Hane.png");
	e_score_img[2] = LoadGraph("Resource/Images/Evaluation/Score_Hapi.png");
	e_score_img[3] = LoadGraph("Resource/Images/Evaluation/Score_Kin.png");

	//エラーチェック
	/*for (int i = 0; i < 4; i++)
	{
		if (e_score_img[i] == -1);
		{
			throw("敵スコア画像が読み込みできませんでした");
		}
	}*/

	type = EFFECT;		//オブジェクトタイプの設定

	Check_active = TRUE;		//表示するかしないか

	toumeido = 255;				//透明度の設定（0が完全透明：255が不完全透明）

	image = NULL;				//画像の設定

	Direction.x = 1.0f;			//移動量の設定
	Direction.y = -1.0f;

	start_location = location;	//初期座標
}

//更新処理
void E_ScoreEffect::Update()
{
	MoveScore();
	EraseAnim();
}

//描画処理
void E_ScoreEffect::Draw() const
{
	//敵が消えるエフェクトの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, toumeido);
	DrawRotaGraphF(location.x, location.y, 0.1, radian, image, TRUE, filp_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//終了時処理
void E_ScoreEffect::Finalize()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(e_score_img[i]);
	}

	image = NULL;
}

void E_ScoreEffect::MoveScore()
{
	//初期座標からどれだけ動いたか
	Vector2D mov_loc = start_location - location;
	if (mov_loc.y > 15.0f)
	{
		Direction.x = 0.5f;
		Direction.y = 1.0f;
	}
	
	location += Direction;
}

//Enemyのスコア取得処理
void E_ScoreEffect::SetScoreImage(int score)
{
	if (score == 200)			//ハコテキの場合
	{
		image = e_score_img[0];
	}
	else if (score == 30)		//ハネテキの場合
	{
		image = e_score_img[1];
	}
	else if (score == -100)		//ハーピィの場合
	{
		image = e_score_img[2];
	}
	else if (score == 1500)		//キンテキの場合
	{
		image = e_score_img[3];
	}

	this->filp_flag = filp_flag;

	if (image == -1)
	{
		throw("ハコテキ画像がありません\n");
	}
}

//アニメーション処理
void E_ScoreEffect::EraseAnim()
{
	//フレームカウントを加算する
	animation_count++;

	//10フレーム目に到達したら
	if (animation_count >= 10)
	{
		//countのリセット
		animation_count = 0;

		//徐々に透明にしていく
		toumeido -= 50;

	}

	//透明度が0以下になった時オブジェクトを消す
	if (toumeido <= 0)
	{
		Check_active = FALSE;
	}
}