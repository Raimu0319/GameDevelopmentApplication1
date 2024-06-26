#include "../../Scene/Scene.h"
#include "Bullet.h"
#include "../Player/Player.h"
#include "DxLib.h"

//コンストラクタ
Bullet::Bullet()
{
	bullet[0] = NULL;
}

//デストラクタ
Bullet::~Bullet()
{

}

//初期化処理
void Bullet::Initialize()
{

	//画像の読み込み
	bullet[0] = LoadGraph("Resource/Images/Enemy/tekitama1.png");

	//エラーチェック
	if (bullet[0] == -1)
	{
		throw("テキ弾の画像がありません\n");
	}


	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 40.0f;

	//オブジェクトタイプの設定
	type = ENEMY_BULLET;

	//表示するかしないか
	Check_active = TRUE;

	//初期画像の設定
	image = bullet[0];
}

//更新処理
void Bullet::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimetionControl();

}

//描画処理
void Bullet::Draw() const
{
	//情報を基に敵画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, 0);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Bullet::Finalize()
{
	DeleteGraph(bullet[0]);
}

//当たり判定通知処理
void Bullet::OnHitCollision(GameObject* hit_object)
{
	//敵同士が触れた場合
	if (hit_object->get_type() == PLAYER)
	{
		//当たった時に行う処理
		direction = 0.0f;

		scene->time_set += scene->time_set / 12 * -1;

		Check_active = FALSE;
	}

}

//位置情報取得処理
Vector2D Bullet::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void Bullet::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//敵弾の移動方向取得処理
void Bullet::SetDirection(const Vector2D& P_Location)
{
	direction = P_Location;
}

//移動処理
void Bullet::Movement()
{
	//画面右端に到達したら、削除する
	if ((640.0f - box_size.x) < (location.x))
	{
		//location.x = box_size.x;
		this->Check_active = FALSE;
	}

	//画面左端に到達したら、削除する
	if (location.x < box_size.x)
	{
		//location.x = (640.0f - box_size.x);
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

//敵アニメーション制御
void Bullet::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{

		image = bullet[0];
		//countのリセット
		animation_count = 0;

	}
}