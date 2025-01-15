#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../PlayerState/Factory/PlayerStateFactory.h"

#include "../../Utility/Singleton.h"

#include "DxLib.h"

Player::Player()
{

}

Player::~Player()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	state = PlayerStateFactory::Get((*this), ePlayerState::eIDLE);
	next_state = ePlayerState::eNONE;

	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = (32.0f, 32.0f);

	// レイヤーの設定
	z_layer = 5;

	//HPの設定
	hit_point = 1;

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Update(float delta_second)
{
	InputManager* input = InputManager::CreateInstance();

	//stateの変更処理
	if (next_state != ePlayerState::eNONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::eNONE;
		now_state = state->GetState();
	}

	////重力速度の計算
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//状態別の更新処理を行う
	state->Update(delta_second);

	//if (velocity.x >= 0.7f)
	//{
	//	velocity.x = 0.7f;
	//}
	//else if (velocity.x <= 0.7f)
	//{
	//	velocity.x = 0.7f;
	//}
	//else
	//{
	//	velocity.x = 0.0f;
	//}



	//摩擦の計算などをした移動の実行
	//velocity =	Vector2D::applyFriction(this->velocity, D_GRAVITY, D_STATIC_FRICTION, D_DYNAMIC_FRICTION, delta_second);
	//direction = Vector2D::applyFriction(this->direction, D_GRAVITY, D_STATIC_FRICTION, D_DYNAMIC_FRICTION, delta_second);

	//移動の実行
	location += velocity * delta_second;
	collision.location = this->location;

	/*if (0.0f > location.x)
	{
		location.x = 0.0f;
	}
	if (640.0f < location.x)
	{
		location.x = 640.0f;
	}*/
	/*if ((640.0f - box_size.x) < location.x)
	{
		location.x = 640.0f - box_size.x;
	}*/

	//330.0f地点を地面と仮定
	if (330.0f < location.y)
	{
		location.y = 330.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}

	AnimationControl(delta_second);

	//// 移動量 * 速さ * 時間 で移動先を決定する
	//location += velocity.y * delta_second;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", this->location.y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "%f", this->velocity.x);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "player_x:%f", this->GetLocation().x);
}

/// <summary>
/// 終了時処理
/// </summary>
void Player::Finalize()
{
	PlayerStateFactory::Finalize();

	// 動的配列の解放
	move_animation.clear();
}

void Player::OnHitCollision(GameObject*)
{
	//プレイヤーの右側がオブジェクトと接触している場合
	if (collision.hitCheck.H_right)
	{
		//右方向に進行できなくする
		if (this->velocity.x > 0)
		{
			velocity.x = 0.0f;

			//めり込んだ分を戻す処理
			float diff
		}
	}
	else if (collision.hitCheck.H_left)
	{
		//左方向に進行できなくする
		if (this->velocity.x < 0)
		{
			velocity.x = 0.0f;

			//めり込んだ分を戻す処理
			//diff
		}
	}
}

void Player::AnimationControl(float delta_second)
{
	switch (now_state)
	{
	case eIDLE:
		image = move_animation[0];
		break;
	case eWALK:
		// 移動中のアニメーション
		animation_time += delta_second;
		if (animation_time >= (1.0f / 10.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 2)
			{
				animation_count = 0;
			}

			image = move_animation[animation_count + 1];
		}

		break;
	case eJUMP:
		image = move_animation[5];
		break;
	case eATTACK:
		break;
	case eDAMAGE:
		break;
	case eGOAL:
		break;
	case eDIE:
		break;
	case eNONE:
		break;
	default:
		break;
	}
}

//次のStateを設定
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}