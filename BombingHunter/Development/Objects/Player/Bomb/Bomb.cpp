#include "Bomb.h"
#include "../../Scene/Scene.h"
#include "BombEffect.h"
#include "../Player.h"
#include "DxLib.h"
#include <math.h>

//コンストラクタ
Bomb::Bomb() : animation_count(0), filp_flag(FALSE)
{
	bomb_img = NULL;
}

//デストラクタ
Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//画像の読み込み
	bomb_img = LoadGraph("Resource/Images/Bomb/Bomb.png");
	
	//エラーチェック
	if (bomb_img == -1)
	{
		throw("爆弾の画像がありません\n");
	}
	
	//向きの設定
	radian = DX_PI / 2.0;

	//当たり判定の大きさ設定
	box_size = 54.0;

	//初期画像の設定
	image = bomb_img;

	//オブジェクトのタイプ
	type = BOMB;

	//表示するかしないか
	Check_active = TRUE;

	//加速度の初期設定
	direction = 0;	
}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();
}

//描画処理
void Bomb::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);

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
	DeleteGraph(bomb_img);
}

void Bomb::GetPlayerpoint(Player* player)
{
	this->player = player;
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->get_type() == ENEMY)
	{
		location.y += direction.y;

		//当たり判定の削除
		box_size = 0.0;

		//このオブジェクトを消す
		Check_active = FALSE;

		//エフェクトの生成
		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
	}
}
 
void Bomb::SetDirection(Vector2D P_velocity)
{
	//プレイヤーが移動しながら爆弾を生成したか
	if (P_velocity.x == 0.0f)
	{
		//まっすぐ下に落ちていく
		direction.y = 2.0f;
		direction_add.y = 0.0f;
	}
	else if (P_velocity.x > 0)
	{
		//プレイヤーの進行方向に応じてふんわりと落ちていく
		direction.x = P_velocity.x;
		direction_add.y = 0.02f;

		//爆弾の角度調整
		radian = atan2f(direction.y, direction.x);							//ｘ/ｙをしてラジアンを計算する

		filp_flag = FALSE;
	}
	else
	{
		//プレイヤーの進行方向に応じてふんわりと落ちていく
		direction.x = P_velocity.x;
		direction_add.y = 0.02f;
		//Vector2D B_dire = direction;

		//爆弾の角度調整
		radian = atan2f(direction.y, direction.x);							//ｘ/ｙをしてラジアンを計算する

		filp_flag = FALSE;
	}
}

//移動処理
void Bomb::Movement()
{
	//爆弾が画面外に到達したときの処理　
	if (location.y > 380.0f)
	{
		direction.y = 0.0f;

		this->Check_active = FALSE;

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
	}

	//画面外に出ないようにする処理
	if ((640.0f - (box_size.x / 2)) < (location.x) || location.x < (box_size.x / 2))
	{
		direction.x = 0.0f;
	}

	//画面上に到達したら、削除する
	if (location.y < 0)
	{
		this->Check_active = FALSE;

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
	}

	//落ちる速度が2.0f以下の場合どんどん加速していく
	if (direction.y <= 2.0f)
	{
		direction.y += direction_add.y;
	}
	
	if (radian != DX_PI / 2.0)
	{
		if (DX_PI / 2.0 < radian)
		{
			radian -= ((DX_PI / 2.0) - radian) / -80;
		}
		else
		{
			radian += ((DX_PI / 2.0) - radian) / 80;
		}
	}

	//現在の位置座標に速さを加算する
	location += direction;
}