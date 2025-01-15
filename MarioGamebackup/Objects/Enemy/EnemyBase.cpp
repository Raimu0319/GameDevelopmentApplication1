#include "EnemyBase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "../../Utility/ResourceManager.h"
#include "../Player/Player.h"
#include "DxLib.h"

#define D_ENEMY_SPEED	(40.0f)

EnemyBase::EnemyBase() :
	now_mode()
{
}

EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize()
{
	//now_mode;					//現在の状態
	//move_animation;		//ゴースト画像
	//eye_animation;		//目の画像
	//direction;			//進行方向
	//e_velocity;				//移動速度
	//start_point;			//初期地点の座標

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

}

//更新処理
void EnemyBase::Update(float delta_second)
{
	//移動処理
	Movement(delta_second);

	//アニメーション制御
	AnimationControl(delta_second);
}

//描画処理
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

}

//終了時処理
void EnemyBase::Finalize()
{
	//move_animation.clear();		//ゴースト画像
}

//当たり判定通知処理
//void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
//{
//	// 当たった、オブジェクトが壁だったら
//	if (hit_object->GetCollision().object_type == eObjectType::wall && collision.is_blocking == true)
//	{
//		// 当たり判定情報を取得して、カプセルがある位置を求める
//		CapsuleCollision hc = hit_object->GetCollision();
//		hc.point[0] += hit_object->GetLocation();
//		hc.point[1] += hit_object->GetLocation();
//
//		// 最近傍点を求める
//		Vector2D near_point = NearPointCheck(hc, this->location);
//
//		// Playerからnear_pointへの方向ベクトルを取得
//		Vector2D dv2 = near_point - this->location;
//		Vector2D dv = this->location - near_point;
//
//		// めり込んだ差分
//		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();
//
//		// diffの分だけ戻る
//		location += dv.Normalize() * diff;
//	}
//}

//移動処理
void EnemyBase::Movement(float delta_second)
{
	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_ENEMY_SPEED * delta_second;
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 16.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;

	//	if (animation_count >= 4)
	//	{
	//		image = animation_num[(enemy_type * 2) + 1];

	//		animation_count = 0;
	//	}

	//	image = animation_num[(enemy_type * 2)];

	//	// 画像の設定
	//	int dir_num = (int)direction;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		eye_image = eye_animation[dir_num];
	//	}

	//}
}