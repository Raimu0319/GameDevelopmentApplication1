#include "../../Scene/Scene.h"
#include "Haneteki.h"
#include "EnemyEffect/EnemyEffect.h"
#include "EnemyEffect/E_ScoreEffect.h"
#include "DxLib.h"

//コンストラクタ
Haneteki::Haneteki()
{
	haneteki[0] = NULL;
	haneteki[1] = NULL;

	happy[0] = NULL;
	happy[1] = NULL;
}

//デストラクタ
Haneteki::~Haneteki()
{

}

//初期化処理
void Haneteki::Initialize()
{
	int i;

	//画像の読み込み
	haneteki[0] = LoadGraph("Resource/Images/Enemy/haneteki1.png");
	haneteki[1] = LoadGraph("Resource/Images/Enemy/haneteki2.png");
	haneteki_SE = LoadSoundMem("Resource/sounds/teki_gahee.wav");		//ハネテキ撃破SE

	happy[0] = LoadGraph("Resource/Images/Enemy/happy1.png");
	happy[1] = LoadGraph("Resource/Images/Enemy/happy2.png");
	hapy_SE = LoadSoundMem("Resource/sounds/pokan.wav");			//ハーピィ撃破SE

	//エラーチェック
	for (i = 0; i < 2; i++)
	{
		if (haneteki[i] == -1)
		{
			throw("ハネテキの画像がありません\n");
		}

		if (happy[i] == -1)
		{
			throw("ハーピィの画像がありません\n");
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
	
	//ハネテキかハーピィか
	RandomSpwan();

	//スコアとSE設定
	if (image == haneteki[0] || image == haneteki[1])
	{
		score = 30;

		sound = haneteki_SE;
	}
	else
	{
		score = -100;

		sound = hapy_SE;
	}
}

//更新処理
void Haneteki::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimetionControl();
}

//描画処理
void Haneteki::Draw() const
{
	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Haneteki::Finalize()
{
	int i;

	//使用した画像を開放
	for (i = 0; i < 2; i++)
	{
		DeleteGraph(haneteki[i]);
		DeleteGraph(happy[i]);
	}

	DeleteSoundMem(haneteki_SE);
	DeleteSoundMem(hapy_SE);
}

//当たり判定通知処理
void Haneteki::OnHitCollision(GameObject* hit_object)
{
	//爆弾と触れた場合
	if (hit_object->get_type() == BOMB)
	{
		//当たった時に行う処理
		direction = 0.0f;

		//スコア加算処理
		scene->Score_count(this->score);

		//SEの再生
		PlaySoundMem(sound, DX_PLAYTYPE_BACK, TRUE);

		//敵が消えるエフェクト
		CreateObject<EnemyEffect>(this->location)->SetImage(this->image, this->flip_flag);

		//自身のスコア表示
		CreateObject<E_ScoreEffect>(this->location)->SetScoreImage(this->score);

		//オブジェクトの削除
		Check_active = FALSE;
	}
}


void Haneteki::RandomSpwan()
{
	int i;
	i = GetRand(5);

	switch (i)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		image = haneteki[0];
		break;

	case 4:
	case 5:
		image = happy[0];
		break;
	}
}


//位置情報取得処理
Vector2D Haneteki::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void Haneteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//移動処理
void Haneteki::Movement()
{
	__super::Movement();
}

//敵アニメーション制御
void Haneteki::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//countのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == haneteki[0])
		{
			image = haneteki[1];
		}
		else if (image == haneteki[1])
		{
			image = haneteki[0];
		}

		if (image == happy[0])
		{
			image = happy[1];
		}
		else if (image == happy[1])
		{
			image = happy[0];
		}
	}
}