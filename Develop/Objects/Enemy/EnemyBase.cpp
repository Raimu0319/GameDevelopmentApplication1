#include "EnemyBase.h"
#include "Ghost/Blinky.h"
#include "../Player/Player.h"
#include "DxLib.h"

EnemyBase::EnemyBase() : player(nullptr), now_mode(START),
move_animation(NULL), eye_animation(NULL), direction(),
e_velocity(0.0f), territory(0.0f), start_point(), enemycreate_court(0)
{
}

EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize()
{
	now_mode;					//現在の状態
	move_animation;		//ゴースト画像
	eye_animation;		//目の画像
	direction;			//進行方向
	e_velocity;				//移動速度
	territory;					//縄張り座標
	start_point;			//初期地点の座標

	player = nullptr;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

}

//更新処理
void EnemyBase::Update(float delta_second)
{
	//状態切り替え
	ModeChange();

	//移動処理
	Movement(delta_second);

	//アニメーション制御
	AnimationControl(delta_second);
}

//描画処理
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	// オフセット値を基にエネミーの目画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
}

//終了時処理
void EnemyBase::Finalize()
{
	move_animation.clear();		//ゴースト画像
	eye_animation.clear();		//目の画像
}

//プレイヤーのポインタを取得
void EnemyBase::GetPlayerpointer(Player* player)
{
	this->player = player;
}

//当たり判定通知処理
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{

}

//状態変更処理
void EnemyBase::ModeChange()
{
	//プレイヤーがパワーアップ状態だった場合イジケ状態になる
	/*if (player->GetPowerUp())
	{
		now_mode = IZIKE;
	}*/
}

//移動処理
void EnemyBase::Movement(float delta_second)
{
	switch (now_mode)
	{
	case START:
		EnemyStart(delta_second);
		break;

	case IZIKE:
		EnemyEscape(delta_second);
		break;

	case CHASE:
		PlayerChase(delta_second);
		break;

	case TERRITORY:
		GoTerritory(delta_second);
		break;

	case DEAD:
		EnemyRespawn(delta_second);
		break;

	default:
		break;
	}
}

//開始時処理
void EnemyBase::EnemyStart(float delta_second)
{

}

//縄張りに向かう処理
void EnemyBase::GoTerritory(float delta_second)
{

}

//プレイヤーを追跡する処理
void EnemyBase::PlayerChase(float delta_second)
{

}

//リスポーン処理
void EnemyBase::EnemyRespawn(float delta_second)
{

}

//いじけ状態
void EnemyBase::EnemyEscape(float delta_second)
{

}

//トンネル通過原則処理
void EnemyBase::EnemyGate()
{

}

//敵キャラ生成処理
void EnemyBase::EnemyCreate(int enemycreate_court)
{
	if (enemycreate_court == 0)
	{
		CreateObject<Blinky>(location);
	}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 16.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;

	//	if (animation_count >= 4)
	//	{
	//		image = animation_num[1];

	//		animation_count = 0;
	//	}

	//	image = animation_num[0];

	//	// 画像の設定
	//	int dir_num = (int)direction;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		eye_image = eye_animation[dir_num];
	//	}

	//}
}