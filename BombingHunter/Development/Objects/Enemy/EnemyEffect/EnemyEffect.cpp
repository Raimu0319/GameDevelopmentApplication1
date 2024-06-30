#include "EnemyEffect.h"
#include "DxLib.h"

EnemyEffect::EnemyEffect() : animation_count(0), filp_flag(0),shake(0),image(NULL),toumeido(255)
{

}

EnemyEffect::~EnemyEffect()
{

}

//初期処理
void EnemyEffect::Initialize()
{
	type = EFFECT;		//オブジェクトタイプの設定

	Check_active = TRUE;				//表示するかしないか

	toumeido = 255;				//画像の透明度

	image = NULL;
}

//更新処理
void EnemyEffect::Update()
{
	MoveEffect();
	EraseAnim();
}

//描画処理
void EnemyEffect::Draw() const
{
	//敵が消えるエフェクトの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, toumeido);
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//終了時処理
void EnemyEffect::Finalize()
{
	image = NULL;
}

//画像の設定
void EnemyEffect::SetImage(int img,int filp_flag)
{
	this->image = img;

	this->filp_flag = filp_flag;
}

//移動処理
void EnemyEffect::MoveEffect()
{
	if (shake == 0)
	{
		location.x += 7.0f;

		shake = 1;
	}
	else
	{
		location.x -= 7.0f;

		shake = 0;
	}

	location.y += 0.5f;
}

//どんどん透明にしていく処理
void EnemyEffect::EraseAnim()
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

	if (toumeido <= 0)
	{
		Check_active = FALSE;
	}
}