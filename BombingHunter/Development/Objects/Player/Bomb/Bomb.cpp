#include "Bomb.h"
#include "../../Scene/Scene.h"
#include "BombEffect.h"
#include "../Player.h"
#include "DxLib.h"
#include <math.h>

//コンストラクタ
Bomb::Bomb() : animation_count(0), filp_flag(FALSE)
{
	animation = NULL;
}

//デストラクタ
Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//画像の読み込み
	animation = LoadGraph("Resource/Images/Bomb/Bomb.png");
	
	//エラーチェック
	if (animation == -1)
	{
		throw("爆弾の画像がありません\n");
	}
	
	//向きの設定
	radian = DX_PI / 2.0;

	//当たり判定の大きさ設定
	box_size = 64.0;

	//初期画像の設定
	image = animation;

	//オブジェクトのタイプ
	type = BOMB;

	//表示するかしないか
	Check_active = TRUE;

	//移動の速さ
	direction = 2.0f;

}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimetionControl();
}

//描画処理
void Bomb::Draw() const
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
void Bomb::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->get_type() == ENEMY)
	{
		//direction = 0.0f;

		location.y += direction.y;

		box_size = 0.0;

		Check_active = FALSE;

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
		
	}
}

//移動処理
void Bomb::Movement()
{
	//爆弾が画面外に到達したときの処理　
	if (location.y > 380.0f)
	{
		direction.y = 0.0f;

		Check_active = FALSE;

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
	}

	//現在の位置座標に速さを加算する
	location.y += direction.y;
}

//アニメーション制御
void Bomb::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 30)
	{
		//countのリセット
		animation_count = 0;

		//画像の切り替え
		
	}
}