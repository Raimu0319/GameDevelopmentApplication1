#include "../../Scene/Scene.h"
#include "Kinteki.h"
#include "Enemy.h"
#include "DxLib.h"

//コンストラクタ
Kinteki::Kinteki()
{
	kinteki[0] = NULL;
	kinteki[1] = NULL;
	kinteki[2] = NULL;
	kinteki[3] = NULL;
	kinteki[4] = NULL;
}

//デストラクタ
Kinteki::~Kinteki()
{

}

//初期化処理
void Kinteki::Initialize()
{
	int i;

	//画像の読み込み
	kinteki[0] = LoadGraph("Resource/Images/Enemy/kinteki.png");
	kinteki[1] = LoadGraph("Resource/Images/Enemy/kinteki1.png");
	kinteki[2] = LoadGraph("Resource/Images/Enemy/kinteki2.png");
	kinteki[3] = LoadGraph("Resource/Images/Enemy/kinteki3.png");
	kinteki[4] = LoadGraph("Resource/Images/Enemy/kinteki4.png");

	//エラーチェック
	for (i = 0; i < 5; i++)
	{
		if (kinteki[i] == -1)
		{
			throw("キンテキの画像がありません\n");
		}
	}

	//初期進行方向の設定
	__super::Initialize();

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 32.0f;

	//オブジェクトタイプの設定
	type = ENEMY;

	//表示するかしないか
	Check_active = TRUE;
	
	image = kinteki[0];
}

//更新処理
void Kinteki::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimetionControl();

}

//描画処理
void Kinteki::Draw() const
{
	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Kinteki::Finalize()
{
	int i;

	for (i = 0; i < 5; i++)
	{
		DeleteGraph(kinteki[i]);
	}

}

//当たり判定通知処理
void Kinteki::OnHitCollision(GameObject* hit_object)
{
	//敵同士が触れた場合
	if (hit_object->get_type() != ENEMY)
	{
		//当たった時に行う処理
		direction = 0.0f;

		Check_active = FALSE;
	}

}

//位置情報取得処理
Vector2D Kinteki::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void Kinteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//移動処理
void Kinteki::Movement()
{
	__super::Movement();
}

//敵アニメーション制御
void Kinteki::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//countのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == kinteki[0])
		{
			image = kinteki[1];
		}
		else if (image == kinteki[1])
		{
			image = kinteki[2];
		}
		else if (image == kinteki[2])
		{
			image = kinteki[3];
		}
		else if (image == kinteki[3])
		{
			image = kinteki[4];
		}
		else if (image == kinteki[4])
		{
			image = kinteki[0];
		}

	}
}