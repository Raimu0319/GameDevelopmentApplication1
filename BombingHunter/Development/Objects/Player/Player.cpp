#include "Player.h"
#include "../Enemy/Enemy.h"
#include "../../Scene/Scene.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include "Bomb/Bomb.h"

//コンストラクタ
Player::Player() : animation_count(0), filp_flag(FALSE),bomb_SE(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Player/飛ぶ1.png");
	animation[1] = LoadGraph("Resource/Images/Player/飛ぶ2.png");

	bomb_SE = LoadSoundMem("Resource/sounds/pan.wav");		//爆弾生成サウンド

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("鳥パイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//当たり判定の大きさ設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];

	//オブジェクトのタイプ
	type = PLAYER;

	//消すか消さないか
	Check_active = TRUE;

	//移動の速さ
	velocity = 0.0f;

	//爆弾の生成上限
	bomb_stop = 0;
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimetionControl();

	//スペースキーを押したら、爆弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		if (bomb_stop == 0)
		{	
			PlaySoundMem(bomb_SE, DX_PLAYTYPE_BACK,TRUE);		//SEの再生
			CreateObject<Bomb>(Vector2D(this->location.x, this->location.y))->SetDirection(this->velocity);
		}
	}
}

//描画処理
void Player::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);
}

//終了時処理
void Player::Finalize()
{
	//使用した画像とSEを解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteSoundMem(bomb_SE);
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object)
{
	
}

//移動処理
void Player::Movement()
{
	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x = -1.0f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = 1.0f;
		filp_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//画面外にいかないように制限する
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if ((640.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 640.0f - (box_size.x / 2.0f);
	}

	//現在の位置座標に速さを加算する
	location += velocity;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//位置情報設定処理
void Player::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//アニメーション制御
void Player::AnimetionControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//countのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}