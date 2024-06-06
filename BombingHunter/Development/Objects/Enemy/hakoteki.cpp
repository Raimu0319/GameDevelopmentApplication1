#include "../../Scene/Scene.h"
#include "hakoteki.h"
#include "Enemy.h"
#include "DxLib.h"

//コンストラクタ
Hakoteki::Hakoteki() : animation_count(0), direction(0.0f)
{
	hakoteki[0] = NULL;
	hakoteki[1] = NULL;
}	

//デストラクタ
Hakoteki::~Hakoteki()
{

}

//初期化処理
void Hakoteki::Initialize()
{
	int i;

	//画像の読み込み
	hakoteki[0] = LoadGraph("Resource/Images/Enemy/hakoteki1.png");
	hakoteki[1] = LoadGraph("Resource/Images/Enemy/hakoteki2.png");
	
	//エラーチェック
	for (i = 0; i < 2; i++)
	{
		if (hakoteki[i] == -1)
		{
			throw("ハコテキ画像がありません\n");
		}
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 40.0f;

	image = hakoteki[0];

	//初期画像の設定
	RandomSpwan();

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);

	//オブジェクトタイプの設定
	type = enemy;

	//表示するかしないか
	Check_active = TRUE;
}

//更新処理
void Hakoteki::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimetionControl();

}

//描画処理
void Hakoteki::Draw() const
{
	//親クラスの描画処理を呼び出す
	__super::Draw();
	/*
	//画像の描画
	DrawRotaGraphF(location.x, location.y, 0.6, 0.0, image, TRUE);

	Vector2D upper_left = location - (box_size / 2.0f);
	Vector2D lower_right = location + (box_size / 2.0f);

	//当たり判定の可視化
	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y, GetColor(255, 0, 0), FALSE);
	*/
}

//終了時処理
void Hakoteki::Finalize()
{
	int i;

	for (i = 0; i < 2; i++)
	{
		DeleteGraph(hakoteki[i]);
	}

}

//当たり判定通知処理
void Hakoteki::OnHitCollision(GameObject* hit_object)
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
Vector2D Hakoteki::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void Hakoteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//移動処理
void Hakoteki::Movement()
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

//敵アニメーション制御
void Hakoteki::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//countのリセット
		animation_count = 0;


		//画像の切り替え
		if (image == hakoteki[0])
		{
			image = hakoteki[1];
		}
		else if (image == hakoteki[1])
		{
			image = hakoteki[0];
		}

	}
}