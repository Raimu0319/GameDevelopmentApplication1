#include "EnemyEffect.h"
#include "DxLib.h"

EnemyEffect::EnemyEffect() : animation_count(0), filp_flag(0),shake(0)
{

}

EnemyEffect::~EnemyEffect()
{

}

void EnemyEffect::Initialize()
{
	Check_active = TRUE;				//表示するかしないか

	toumeido = 255;

	image = NULL;
}

void EnemyEffect::Update()
{
	EraseAnim();
}

void EnemyEffect::Draw() const
{
	//敵が消えるエフェクトの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, toumeido);
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void EnemyEffect::Finalize()
{
	image = NULL;
}

void EnemyEffect::SetImage(int img,int filp_flag)
{
	this->image = img;

	this->filp_flag = filp_flag;

	if (image == -1)
	{
		throw("ハコテキ画像がありません\n");
	}
}

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

		if (shake == 0)
		{
			location.x += 5.0f;
			
			shake = 1;
		}
		else
		{
			location.x -= 5.0f;

			shake = 0;
		}

		location.y += 2.0f;

	}

	if (toumeido <= 0)
	{
		Check_active = FALSE;
	}
}