#include "../../Scene/Scene.h"
#include "Hakoteki.h"
#include "Bullet.h"
#include "DxLib.h"

//コンストラクタ
Hakoteki::Hakoteki()
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

	//初期進行方向の設定
	__super::Initialize();

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 40.0f;

	//オブジェクトタイプの設定
	type = ENEMY;

	//表示するかしないか
	Check_active = TRUE;
	
	//初期画像の設定
	image = hakoteki[0];
}

//更新処理
void Hakoteki::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimetionControl();

	//弾の生成
	BulletCreate();

}

//描画処理
void Hakoteki::Draw() const
{
	//親クラスの描画処理を呼び出す
	__super::Draw();
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
	if (hit_object->get_type() == PLAYER)
	{
		//当たった時に行う処理
		direction = 0.0f;

		Check_active = FALSE;
	}

}

void Hakoteki::BulletCreate()
{
	wait_count++;

	//弾の生成処理
	if (wait_count >= 120)
	{
		int r;

		r = GetRand(5);

		if (r <= 2)
		{
			//弾の生成
			CreateObject<Bullet>(Vector2D(this->location.x, this->location.y));
		}

		wait_count = 0;
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
	__super::Movement();
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