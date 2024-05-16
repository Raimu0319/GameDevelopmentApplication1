#include"Enemy.h"
#include"DxLib.h"

//コンストラクタ
Enemy::Enemy() : animation_count(0), filp_flag(FALSE)
{
	hakoteki[0] = NULL;
	hakoteki[1] = NULL;

	haneteki[0] = NULL;
	haneteki[1] = NULL;

	happy[0] = NULL;
	happy[1] = NULL;

	kinteki[0] = NULL;
	kinteki[1] = NULL;
	kinteki[2] = NULL;
	kinteki[3] = NULL;
	kinteki[4] = NULL;
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//初期化用関数
	int i;

	//画像の読み込み
	hakoteki[0] = LoadGraph("Resource/Images/Enemy/hakoteki1.png");
	hakoteki[1] = LoadGraph("Resource/Images/Enemy/hakoteki2.png");

	haneteki[0] = LoadGraph("Resource/Images/Enemy/haneteki1.png");
	haneteki[1] = LoadGraph("Resource/Images/Enemy/haneteki2.png");

	happy[0] = LoadGraph("Resource/Images/Enemy/happy1.png");
	happy[1] = LoadGraph("Resource/Images/Enemy/happy2.png");

	kinteki[0] = LoadGraph("Resource/Images/Enemy/kinteki.png");
	kinteki[1] = LoadGraph("Resource/Images/Enemy/kinteki1.png");
	kinteki[2] = LoadGraph("Resource/Images/Enemy/kinteki2.png");
	kinteki[3] = LoadGraph("Resource/Images/Enemy/kinteki3.png");
	kinteki[4] = LoadGraph("Resource/Images/Enemy/kinteki4.png");

	//エラーチェック
	for (i = 0; i < 2; i++)
	{
		if (hakoteki[i] == -1)
		{
			throw("ハコテキの画像がありません\n");
		}

		if (haneteki[i] == -1)
		{
			throw("ハネテキの画像がありません\n");
		}

		if (happy[i] == -1)
		{
			throw("ハーピィの画像がありません\n");
		}

	}

	for (i = 0; i < 5; i++)
	{
		if (hakoteki[i] == -1)
		{
			throw("キンテキの画像がありません\n");
		}
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	scale = 32.0f;

	//初期画像の設定
	image = hakoteki[0];
}

//更新処理
void Enemy::Update()
{
	//右に進み続ける
	location.x += 1.0f;

	//右端に行くと左端に戻る
	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}
}

//描画処理
void Enemy::Draw() const
{
	//画像の描画
	DrawRotaGraphF(location.x, location.y, 0.6, 0.0, image, TRUE);

	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	//当たり判定の可視化
	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y, GetColor(255,0,0), FALSE);
}

//終了時処理
void Enemy::Finalize()
{

}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
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

//敵アニメーション制御
void Enemy::EnemyAnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//countのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == hakoteki[0])
		{
			image = hakoteki[1];
		}
		else
		{
			image = hakoteki[0];
		}
	}
}