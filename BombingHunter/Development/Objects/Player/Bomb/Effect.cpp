#include "Bomb.h"
#include "Effect.h"
#include "../../Scene/Scene.h"
#include "DxLib.h"

//コンストラクタ
Effect::Effect() : animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
}

//デストラクタ
Effect::~Effect()
{

}

//初期化処理
void Effect::Initialize()
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
	type = effect;

	//表示するかしないか
	Check_active = TRUE;

}

//更新処理
void Effect::Update()
{
	////移動処理
	//Movement();
	//アニメーション制御
	AnimetionControl();
}

//描画処理
void Effect::Draw() const
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
void Effect::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
}

//当たり判定通知処理
void Effect::OnHitCollision(GameObject* hit_object)
{
	/*if (hit_object->get_type() == FALSE)
	{

	}*/
}

//移動処理
void Effect::Movement()
{
	////爆弾が画面外に到達したときの処理　
	//if (location.y > 480.0f)
	//{
	//	direction.y = 0.0f;

	//	Check_active = FALSE;

	//}

	////画像が爆発エフェクトの場合
	//if (image == animation[1] || image == animation[2] ||
	//	image == animation[3])
	//{
	//	direction.y = 0.0f;
	//}

	////現在の位置座標に速さを加算する
	//location.y += direction.y;
}

//アニメーション制御
void Effect::AnimetionControl()
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