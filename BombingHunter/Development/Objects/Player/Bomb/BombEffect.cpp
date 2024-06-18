#include "Bomb.h"
#include "BombEffect.h"
#include "../../Scene/Scene.h"
#include "DxLib.h"

//コンストラクタ
BombEffect::BombEffect() : animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
}

//デストラクタ
BombEffect::~BombEffect()
{

}

//初期化処理
void BombEffect::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bomb/bakuhatu1.png");
	animation[1] = LoadGraph("Resource/Images/Bomb/bakuhatu2.png");
	animation[2] = LoadGraph("Resource/Images/Bomb/bakuhatu3.png");

	//エラーチェック
	for (int i = 0; i < 3; i++)
	{
		if (animation[i] == -1)
		{
			throw("爆弾の画像がありません\n");
		}
	}

	//向きの設定
	radian = 0.0;

	//当たり判定の大きさ設定
	box_size = 0.0;

	//初期画像の設定
	image = animation[0];

	//オブジェクトのタイプ
	type = EFFECT;

	//表示するかしないか
	Check_active = TRUE;

}

//更新処理
void BombEffect::Update()
{
	////移動処理
	//Movement();
	//アニメーション制御
	AnimetionControl();
}

//描画処理
void BombEffect::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);

	//デバック用
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);

#endif
}

//終了時処理
void BombEffect::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
}

//当たり判定通知処理
void BombEffect::OnHitCollision(GameObject* hit_object)
{
	/*if (hit_object->get_type() == FALSE)
	{

	}*/
}

//移動処理
void BombEffect::Movement()
{
	
}

//アニメーション制御
void BombEffect::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 30)
	{
		//countのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if (image == animation[1])
		{
			image = animation[2];

			Check_active = FALSE;
		}
	}
}