#include "../../Scene/Scene.h"
#include "Hakoteki.h"
#include "EnemyEffect/EnemyEffect.h"
#include "EnemyEffect/E_ScoreEffect.h"
#include "../Player/Player.h"
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

	//スコアの設定
	score = 200;
	
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
	//爆弾と触れた場合
	if (hit_object->get_type() == BOMB)
	{
		//当たった時に行う処理
		direction = 0.0f;

		//スコア加算処理
		scene->Score_count(this->score);

		//敵が消えるエフェクト
		CreateObject<EnemyEffect>(this->location)->SetImage(this->image, this->flip_flag);

		//自身のスコア表示
		CreateObject<E_ScoreEffect>(this->location)->SetScoreImage(this->score);

		//オブジェクトの削除
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
			//プレイヤーとハコテキの距離を求めて角度を求める
			//プレイヤーとハコテキの距離を求める
			Vector2D vec = player->GetLocation() - this->location;
			float r = atan2f(vec.y, vec.x);							//ｘ/ｙをしてラジアンを計算する
			Vector2D B_direction = Vector2D((cosf(r)), (sinf(r)));	//上の計算結果の値をcosfとsinfに渡してあげると角度が出る
			//弾の生成
 			CreateObject<Bullet>(Vector2D(this->location.x, this->location.y))->SetDirection(B_direction);

			//atan2fは角度を求める
			//cosfがyの比率を求める
			//sinfがxの比率を求める
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

void Hakoteki::GetPlayerpoint(Player* player)
{
	this->player = player;
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