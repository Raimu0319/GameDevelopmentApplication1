#include "EnemyBase.h"
#include "Ghost/Blinky.h"
#include "Ghost/Pinky.h"
#include "Ghost/Clyde.h"
#include "Ghost/Inky.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "../../Utility/ResourceManager.h"
#include "../Player/Player.h"
#include "DxLib.h"

#define D_ENEMY_SPEED	(55.0f)

EnemyBase::EnemyBase() :
	player(nullptr), now_mode(START)
	,move_animation(NULL), eye_animation(NULL)
	,direction(E_RIGHT),e_velocity(0.0f)
	,territory(0.0f), start_point()
	,enemycreate_court(0),eye_image(NULL)
	,izke_time(0.0f),search_end(false)
{
}

EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize()
{
	//now_mode;					//現在の状態
	//move_animation;		//ゴースト画像
	//eye_animation;		//目の画像
	//direction;			//進行方向
	//e_velocity;				//移動速度
	//start_point;			//初期地点の座標

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

}

//更新処理
void EnemyBase::Update(float delta_second)
{
	//移動処理
	Movement(delta_second);

	ModeChange(delta_second);

	//アニメーション制御
	AnimationControl(delta_second);

	
	old_direction = direction;
}

//描画処理
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	if (now_mode != IZIKE)
	{
		// オフセット値を基にエネミーの目画像の描画を行う
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}

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
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}
}

//状態変更処理
void EnemyBase::ModeChange(float delta_second)
{
	//プレイヤーがパワーアップ状態だった場合イジケ状態になる
	if (player->GetPowerUp())
	{
		now_mode = IZIKE;
	}
	
	//現在状態がイジケ状態なら
	if (now_mode == IZIKE)
	{
		now_time += delta_second;
		if (now_time >= (1.0f / 16.0f))
		{
			now_time = 0.0f;
			izke_time++;
			//一定時間経過したらプレイヤーのパワーを下げてモードを戻す。
			if (izke_time >= 40)
			{
				now_mode = CHASE;
				player->SetPowerDown();
				izke_time = 0.0f;
			}
		}
	}
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

	// 移動方向に移動していなければ direction_state を変更する
	switch (direction)
	{
	case eDirectionState::E_UP:
	case eDirectionState::E_DOWN:
	{
		float diff = location.y - old_location.y;
		if (((direction == eDirectionState::E_UP) && (diff < 0.0f)) ||
			((direction == eDirectionState::E_DOWN) && (0.0f < diff)))
		{
			// 移動方向に移動してるので break
			break;
		}

		e_velocity.y = 0.0f;

	}
	break;

	case eDirectionState::E_LEFT:
	case eDirectionState::E_RIGHT:
	{

		float diff = location.x - old_location.x;
		if (((direction == eDirectionState::E_LEFT) && (diff < 0.0f)) ||
			((direction == eDirectionState::E_RIGHT) && (0.0f < diff)))
		{
			// 移動方向に移動してるので break
			break;
		}

		e_velocity.x = 0.0f;
	}
	break;

	default:// 何もしない
		break;
	}

	// 進行方向の移動量を追加
	switch (direction)
	{
	case eDirectionState::E_UP:
		e_velocity.y = -3.0f;
		break;
	case eDirectionState::E_DOWN:
		e_velocity.y = 3.0f;
		break;
	case eDirectionState::E_LEFT:
		e_velocity.x = -3.0f;
		break;
	case eDirectionState::E_RIGHT:
		e_velocity.x = 3.0f;
		break;
	default:
		break;
	}

	// 移動量 * 速さ * 時間 で移動先を決定する
	location += e_velocity * D_ENEMY_SPEED * delta_second;
}

//開始時処理
void EnemyBase::EnemyStart(float delta_second)
{

}

//縄張りに向かう処理
void EnemyBase::GoTerritory(float delta_second)
{
	switch (enemy_type)
	{
	case BLINKY:
	{
		// 現在パネルの状態を確認
		ePanelID panel = StageData::GetPanelData(location);

		//現在パネルがブランチなら
		if (panel == BRANCH)
		{
			//上下左右のパネル情報
			std::map<eAdjacentDirection, ePanelID> panel = {
				{ eAdjacentDirection::UP, ePanelID::NONE },
				{ eAdjacentDirection::DOWN, ePanelID::NONE },
				{ eAdjacentDirection::LEFT, ePanelID::NONE },
				{ eAdjacentDirection::RIGHT, ePanelID::NONE }
			};

			//ルート保存
			std::vector<std::vector<float>> root;

			//上下左右のパネル情報の取得
			panel = StageData::GetAdjacentPanelData(location);

			//計算式を書く　F = H + G (H::プレイヤーとエネミーの距離 G::現在位置から何回動くか)
			loc_diff = territory - location;

			//探索が終了しているかどうか
			while (search_end == false)
			{
				//移動コスト
				move_cost += 1.0f;

				//パネルが壁以外なら
				if (panel[eAdjacentDirection::UP] != WALL)
				{
					//移動コストがどれほどか計算
					sum_cost = move_cost + ((territory.x - location.x) + (territory.y - location.y));

					root.push_back(location) ;
				}

				if (panel[eAdjacentDirection::DOWN] != WALL)
				{
					

				}

				if (panel[eAdjacentDirection::LEFT] != WALL)
				{
					

				}

				if (panel[eAdjacentDirection::RIGHT] != WALL)
				{
					

				}

				//現在位置が縄張りと近かったら
				if (location.x == territory.x && location.y == territory.y)
				{
					search_end = true;
				}
				
			}

			//if (panel[eAdjacentDirection::UP] != WALL)
			//{			
			//	//進行方向と逆の方向に進まないようにする
			//	if (old_direction != E_DOWN)
			//	{
			//		direction = E_UP;
			//	}

			//	//Fの値が一番小さい所に向かって動く
			//}

			//if (panel[eAdjacentDirection::DOWN] != WALL)
			//{
			//	//進行方向と逆の方向に進まないようにする
			//	if (old_direction != E_UP)
			//	{
			//		direction = E_DOWN;
			//	}
			//	
			//}

			//if (panel[eAdjacentDirection::LEFT] != WALL)
			//{
			//	//進行方向と逆の方向に進まないようにする
			//	if (old_direction != E_RIGHT)
			//	{
			//		direction = E_LEFT;
			//	}

			//}

			//if (panel[eAdjacentDirection::RIGHT] != WALL)
			//{
			//	//進行方向と逆の方向に進まないようにするｄ
			//	if (old_direction != E_LEFT)
			//	{
			//		direction = E_RIGHT;
			//	}
			//	
			//}


		}
		//if (panel == BRANCH)
		//{

		//}

		/*if (territory.x < location.x)
		{
			direction = E_LEFT;
		}
		else
		{
			direction = E_RIGHT;
		}

		if (territory.y < location.y)
		{
			direction = E_UP;
		}
		else
		{
			direction = E_DOWN;
		}*/
	}

		break;
	case PINKY:
		break;
	case CLYDE:
		break;
	case INKY:
		break;
	default:
		break;
	}
}

//プレイヤーを追跡する処理
void EnemyBase::PlayerChase(float delta_second)
{
	/*switch (enemy_type)
	{
	case BLINKY:
		if (player->GetLocation() - this->location)
		{

		}
		break;
	case PINKY:
		break;
	case CLYDE:
		break;
	case INKY:
		break;
	default:
		break;
	}*/
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
	//		image = animation_num[(enemy_type * 2) + 1];

	//		animation_count = 0;
	//	}

	//	image = animation_num[(enemy_type * 2)];

	//	// 画像の設定
	//	int dir_num = (int)direction;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		eye_image = eye_animation[dir_num];
	//	}

	//}
}