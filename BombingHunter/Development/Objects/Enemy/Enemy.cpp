#include "../../Scene/Scene.h"
#include "Enemy.h"
#include "Hakoteki.h"
#include "Haneteki.h"
#include "Kinteki.h"
#include "DxLib.h"

//コンストラクタ
Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//1～0の数字をランダムで取得
	int r = GetRand(1);

	//エネミーのスピードをランダムに設定する
	float speed = (GetRand(2) % 2 * 0.5) + 1.0f;

	//rが1なら左から右に移動	rが0なら右から左に移動
	if (r == 1)
	{
		// 右向き
		direction = Vector2D(speed, 0.0f);
		this->location.x = 80.0f;
	}
	else
	{
		// 左向き
		direction = Vector2D(-speed, 0.0f);
		this->location.x = 580.0f;
	}
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimetionControl();
}

//描画処理
void Enemy::Draw() const
{

	//情報を基に敵画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
	
}

//終了時処理
void Enemy::Finalize()
{

}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	
}

//位置情報取得処理
Vector2D Enemy::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void Enemy::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//移動処理
void Enemy::Movement()
{
	//画像反転フラグ
	flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//画面右端に到達したら、削除する
	if ((640.0f - box_size.x) < (location.x / 2))
	{
		this->Check_active = FALSE;
	}

	//画面左端に到達したら、削除する
	if (location.x < (box_size.x / 2))
	{
		this->Check_active = FALSE;
	}

	//画面上に到達したら、削除する
	if (location.y < 0)
	{
		this->Check_active = FALSE;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

void Enemy::RandomSpwan()
{

}

//敵アニメーション制御
void Enemy::AnimetionControl()
{
	
}