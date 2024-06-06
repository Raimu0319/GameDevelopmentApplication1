#include "../../Scene/Scene.h"
#include "Enemy.h"
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
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = TRUE;
	}
	else
	{
		flip_flag = FALSE;
	}

	//情報を基に敵画像を描画する
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
	
}

//終了時処理
void Enemy::Finalize()
{
	//int i;

	////使用した画像を開放
	//for (i = 0; i < 2; i++)
	//{
	//	DeleteGraph(hakoteki[i]);
	//	DeleteGraph(haneteki[i]);
	//	DeleteGraph(happy[i]);
	//}

	//for (i = 0; i < 4; i++)
	//{
	//	DeleteGraph(kinteki[i]);
	//}


}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//敵同士が触れた場合
	if (hit_object->get_type() != enemy)
	{
		//当たった時に行う処理
		direction = 0.0f;

		Check_active = FALSE;
	}	
	
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
	//画面右端に到達したら、左端に戻る
	//if (((location.x + direction.x) < box_size.x) ||(640.0f - box_size.x) < (location.x + direction.x))
	if ((640.0f - box_size.x) < (location.x + direction.x))
	{
		location.x = -1.0f;
		direction.x *= 1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(480.0f - box_size.y) < (location.y + direction.y))
	{
		location.x = 630;
		direction.y *= -1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

void Enemy::RandomSpwan()
{
	/*int i;
	i =  GetRand(6);

	switch (i)
	{
	case 0:
	case 1:
	case 2:
		image = hakoteki[0];
		break;
	
	case 3:
	case 4:
		image = haneteki[0];
		break;

	case 5:
		image = happy[0];
		break;

	case 6:
		image = kinteki[0];
		break;

	}*/
}

//敵アニメーション制御
void Enemy::AnimetionControl()
{
	////フレームカウントを加算する
	//animation_count++;

	////30フレーム目に到達したら
	//if (animation_count >= 30)
	//{
	//	//countのリセット
	//	animation_count = 0;
	//

	//	//画像の切り替え
	//	if (image == hakoteki[0])
	//	{
	//		image = hakoteki[1];
	//	}
	//	else if (image == hakoteki[1])
	//	{
	//		image = hakoteki[0];
	//	}

	//	if (image == haneteki[0])
	//	{
	//		image = haneteki[1];
	//	}
	//	else if(image == haneteki[1])
	//	{
	//		image = haneteki[0];
	//	}

	//	if (image == happy[0])
	//	{
	//		image = happy[1];
	//	}
	//	else if (image == happy[1])
	//	{
	//		image = happy[0];
	//	}

	//}
}