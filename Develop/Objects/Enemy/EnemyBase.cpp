#include "EnemyBase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "../../Utility/ResourceManager.h"
#include "../Player/Player.h"
#include "DxLib.h"

#define D_ENEMY_SPEED	(40.0f)

EnemyBase::EnemyBase() :
	player(nullptr), now_mode(START)
	,move_animation(NULL), eye_animation(NULL)
	,direction(E_RIGHT),e_velocity(0.0f)
	,territory(0.0f,0.0f), start_point()
	,enemycreate_court(0),eye_image(NULL)
	,izke_time(0.0f),search_end(false)
	,old_loc(NULL), gate_point(350.0f, 330.0f)
	, mode_time(0.0f)
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

	//territory = (-200, -200);

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

	DrawFormatString(10, 10, GetColor(255, 255, 255), "%d", (int)now_mode);
	DrawFormatString(10, 820, GetColor(255, 255, 255), "%.2f, %.2f", territory.x, territory.y);
	DrawFormatString(10, 836, GetColor(255, 255, 255), "%.2f, %.2f", player->GetLocation().x, player->GetLocation().y);

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
	if (hit_object->GetCollision().object_type == eObjectType::wall && collision.is_blocking == true)
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
	if (player->GetPowerUp() && now_mode != START)
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
			if (izke_time >= 80)
			{
				now_mode = TERRITORY;
				player->SetPowerDown();
				izke_time = 0.0f;
			}
		}
	}

	now_time += delta_second;
	if (now_time >= (1.0f / 16.0f))
	{
		now_time = 0.0f;
		mode_time++;

		if (mode_time >= 200)
		{
			//もし縄張り状態なら追いかけモード
			if (now_mode == TERRITORY)
			{
				now_mode = CHASE;

				mode_time = 0;
			}
			else if (now_mode == CHASE) //もし追いかけモードなら縄張り状態に変更
			{
				now_mode = TERRITORY;

				mode_time = 0;
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

		//もしコリジョンフラッグが有効なら
		if (collision.is_blocking == true)
		{
			e_velocity.y = -2.0f;
			e_velocity.x = 0.0f;
		}
		else if(collision.is_blocking == false)
		{
			e_velocity.y = -1.0f;
			e_velocity.x = 0.0f;
		}

		break;
	case eDirectionState::E_DOWN:
		e_velocity.y = 2.0f;
		e_velocity.x = 0.0f;
		break;
	case eDirectionState::E_LEFT:
		e_velocity.x = -2.0f;
		e_velocity.y = 0.0f;
		break;
	case eDirectionState::E_RIGHT:
		e_velocity.x = 2.0f;
		e_velocity.y = 0.0f;
		break;
	case eDirectionState::E_NONE:
		e_velocity.x = 0.0f;
		e_velocity.y = 0.0f;
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
	if (now_mode == START)
	{
		switch (enemy_type)
		{
		case BLINKY:
			break;
		case PINKY:
			if (player->GetFoodCount() >= 20)
			{
				if (collision.is_blocking == true)
				{
					//ゲートの位置座標を添え字に変換
					int x, y;

					//現在位置をint型に変換して保存
					int loc_x = (int)location.x;
					int loc_y = (int)location.y;
					/*location.x = 350.0f;
					location.y = 274.0f;*/

					//現在位置を添え字に変換
					StageData::ConvertToIndex(gate_point, y, x);

					//現在位置を添え字に変換
					StageData::ConvertToIndex(location, ey, ex);

					//ゲートのまでの位置を探索
					RootSearch(x, y);

					//現在パネルの中心座標を取得
					int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
					int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

					//現在タイルの情報を取得
					ePanelID panel = StageData::GetPanelData(location);

					//現在パネルがゲートと重なったら
					if (ex == x && ey == y)
					{
						collision.is_blocking = false;

						direction = E_UP;
					}
				}
				else
				{
		
					//初期地点から出たらコリジョンを有効にする
					if (location.y < 275.0f)
					{
						collision.is_blocking = true;

						now_mode = TERRITORY;

						direction = E_RIGHT;
					}

				}

				
			}
			else
			{
				//上下左右のパネル情報
				std::map<eAdjacentDirection, ePanelID> panel = {
					{ eAdjacentDirection::UP, ePanelID::NONE },
					{ eAdjacentDirection::DOWN, ePanelID::NONE },
					{ eAdjacentDirection::LEFT, ePanelID::NONE },
					{ eAdjacentDirection::RIGHT, ePanelID::NONE }
				};

				//上下左右のパネル情報の取得
				panel = StageData::GetAdjacentPanelData(location);

				//パネルが壁以外なら
				if (panel[eAdjacentDirection::UP] == WALL)
				{
					direction = E_DOWN;
				}

				//パネルが壁以外なら
				if (panel[eAdjacentDirection::DOWN] == WALL)
				{
					direction = E_UP;
				}

			}

			break;

		case CLYDE:
			if (player->GetFoodCount() >= 40)
			{
				if (collision.is_blocking == true)
				{
					//ゲートの位置座標を添え字に変換
					int x, y;

					//現在位置をint型に変換して保存
					int loc_x = (int)location.x;
					int loc_y = (int)location.y;
					/*location.x = 350.0f;
					location.y = 274.0f;*/

					//現在位置を添え字に変換
					StageData::ConvertToIndex(gate_point, y, x);

					//現在位置を添え字に変換
					StageData::ConvertToIndex(location, ey, ex);

					//ゲートのまでの位置を探索
					RootSearch(x, y);

					//現在パネルの中心座標を取得
					int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
					int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

					//現在タイルの情報を取得
					ePanelID panel = StageData::GetPanelData(location);

					//現在パネルがゲートと重なったら
					if (ex == x && ey == y)
					{
						collision.is_blocking = false;

						direction = E_UP;
					}
				}
				else
				{

					//初期地点から出たらコリジョンを有効にする
					if (location.y < 275.0f)
					{
						collision.is_blocking = true;

						now_mode = TERRITORY;

						direction = E_RIGHT;
					}

				}


			}
			else
			{
				//上下左右のパネル情報
				std::map<eAdjacentDirection, ePanelID> panel = {
					{ eAdjacentDirection::UP, ePanelID::NONE },
					{ eAdjacentDirection::DOWN, ePanelID::NONE },
					{ eAdjacentDirection::LEFT, ePanelID::NONE },
					{ eAdjacentDirection::RIGHT, ePanelID::NONE }
				};

				//上下左右のパネル情報の取得
				panel = StageData::GetAdjacentPanelData(location);

				//パネルが壁以外なら
				if (panel[eAdjacentDirection::UP] == WALL)
				{
					direction = E_DOWN;
				}

				//パネルが壁以外なら
				if (panel[eAdjacentDirection::DOWN] == WALL)
				{
					direction = E_UP;
				}

			}
			break;

		case INKY:
			if (player->GetFoodCount() >= 50)
			{
				if (collision.is_blocking == true)
				{
					//ゲートの位置座標を添え字に変換
					int x, y;

					//現在位置をint型に変換して保存
					int loc_x = (int)location.x;
					int loc_y = (int)location.y;
					/*location.x = 350.0f;
					location.y = 274.0f;*/

					//現在位置を添え字に変換
					StageData::ConvertToIndex(gate_point, y, x);

					//現在位置を添え字に変換
					StageData::ConvertToIndex(location, ey, ex);

					//ゲートのまでの位置を探索
					RootSearch(x, y);

					//現在パネルの中心座標を取得
					int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
					int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

					//現在タイルの情報を取得
					ePanelID panel = StageData::GetPanelData(location);

					//現在パネルがゲートと重なったら
					if (ex == x && ey == y)
					{
						collision.is_blocking = false;

						direction = E_UP;
					}
				}
				else
				{

					//初期地点から出たらコリジョンを有効にする
					if (location.y < 275.0f)
					{
						collision.is_blocking = true;

						now_mode = TERRITORY;

						direction = E_RIGHT;
					}

				}


			}
			else
			{
				//上下左右のパネル情報
				std::map<eAdjacentDirection, ePanelID> panel = {
					{ eAdjacentDirection::UP, ePanelID::NONE },
					{ eAdjacentDirection::DOWN, ePanelID::NONE },
					{ eAdjacentDirection::LEFT, ePanelID::NONE },
					{ eAdjacentDirection::RIGHT, ePanelID::NONE }
				};

				//上下左右のパネル情報の取得
				panel = StageData::GetAdjacentPanelData(location);

				//パネルが壁以外なら
				if (panel[eAdjacentDirection::UP] == WALL)
				{
					direction = E_DOWN;
				}

				//パネルが壁以外なら
				if (panel[eAdjacentDirection::DOWN] == WALL)
				{
					direction = E_UP;
				}

			}
			break;

		default:
			break;
		}
	}
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
	//現在位置をint型に変換して保存
	int loc_x = (int)location.x;
	int loc_y = (int)location.y;

	//現在位置を添え字に変換
	StageData::ConvertToIndex(location, ey, ex);

	//現在パネルの中心座標を取得
	int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
	int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

	//中心座標の合計値
	int e_sum = ex_center + ey_center;

	//現在タイルの情報を取得
	ePanelID panel = StageData::GetPanelData(location);

	int random;
	random = GetRand(4);

	//現在パネルが中心かつブランチもしくは現在モードがスタート状態なら（前回座標と同じなら入らない）
	if (((loc_x + 1 || loc_x == ex_center && loc_y + 1 || loc_y == ey_center)) && (panel == BRANCH || now_mode == START)
		&& (e_sum != old_loc))
	{
		//上下左右のパネル情報
		std::map<eAdjacentDirection, ePanelID> panel = {
			{ eAdjacentDirection::UP, ePanelID::NONE },
			{ eAdjacentDirection::DOWN, ePanelID::NONE },
			{ eAdjacentDirection::LEFT, ePanelID::NONE },
			{ eAdjacentDirection::RIGHT, ePanelID::NONE }
		};

		switch (random)
		{
		case 0:
			//パネルが壁以外なら
			if (panel[eAdjacentDirection::UP] != WALL && direction != E_DOWN)
			{
				direction = E_UP;
				break;
			}
		case 1:
			//パネルが壁以外なら
			if (panel[eAdjacentDirection::DOWN] != WALL && direction != E_UP)
			{
				direction = E_DOWN;
				break;
			}

		case 2:
			//パネルが壁以外なら
			if (panel[eAdjacentDirection::LEFT] != WALL && direction != E_RIGHT)
			{
				direction = E_LEFT;
				break;
			}

		case 3:
			//パネルが壁以外なら
			if (panel[eAdjacentDirection::RIGHT] != WALL && direction != E_LEFT)
			{
				direction = E_RIGHT;
				break;
			}
		default:
			break;
		}

	}	

}

//トンネル通過原則処理
void EnemyBase::EnemyGate()
{

}

//目標のパネル座標を渡すと最短距離で向かう処理
void EnemyBase::RootSearch(int x, int y)
{
	//現在位置をint型に変換して保存
	int loc_x = (int)location.x;
	int loc_y = (int)location.y;

	//現在位置を添え字に変換
	StageData::ConvertToIndex(location, ey, ex);

	//現在パネルの中心座標を取得
	int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
	int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

	//中心座標の合計値
	int e_sum = ex_center + ey_center;

	//現在タイルの情報を取得
	ePanelID panel = StageData::GetPanelData(location);

	//現在パネルが中心かつブランチもしくは現在モードがスタート状態なら（前回座標と同じなら入らない）
	if (((loc_x + 1 || loc_x == ex_center && loc_y + 1 || loc_y == ey_center)) && (panel == BRANCH || now_mode == START)
		&& (e_sum != old_loc))
	{
		//上下左右のパネル情報
		std::map<eAdjacentDirection, ePanelID> panel = {
			{ eAdjacentDirection::UP, ePanelID::NONE },
			{ eAdjacentDirection::DOWN, ePanelID::NONE },
			{ eAdjacentDirection::LEFT, ePanelID::NONE },
			{ eAdjacentDirection::RIGHT, ePanelID::NONE }
		};

		//float reserve_root[5] = { 9999, 9999, 9999, 9999, 9999 };				//評価が同じだった場合片方を保存しておく配列

		//上下左右の評価保存配列
		int top = 99999;
		int down = 99999;
		int right = 99999;
		int left = 99999;

		//評価保存、ルート保存
		//int reserve_root[2] = { 99999,99999 };

		//評価の合計値、最小値
		int sum_cost = 0;
		int min_cost = 0;

		//次の移動方向
		eDirectionState next_root = E_NONE;

		//現在位置と縄張りの差
		int loc_dif = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

		//move_cost = 0;

		//上下左右のパネル情報の取得
		panel = StageData::GetAdjacentPanelData(location);

		//移動コスト
		//move_cost++;

			//パネルが壁以外なら
		if (panel[eAdjacentDirection::UP] != WALL && direction != E_DOWN)
		{
			ey -= 1;

			//移動コストがどれほどか計算
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//評価の保存
			top = sum_cost + loc_dif;

			ey += 1;
		}
		else    //壁だった場合
		{
			top = 99999;
		}

		if (panel[eAdjacentDirection::DOWN] != WALL && direction != E_UP)
		{
			ey += 1;

			//移動コストがどれほどか計算
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//評価の保存
			down = sum_cost + loc_dif;

			ey -= 1;
		}
		else    //壁だった場合
		{
			down = 99999;
		}

		if (panel[eAdjacentDirection::LEFT] != WALL && direction != E_RIGHT)
		{
			ex -= 1;

			//移動コストがどれほどか計算
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//評価の保存
			left = sum_cost + loc_dif;

			ex += 1;
		}
		else    //壁だった場合
		{
			left = 99999;
		}

		if (panel[eAdjacentDirection::RIGHT] != WALL && direction != E_LEFT)
		{
			ex += 1;

			//移動コストがどれほどか計算
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//評価の保存
			right = sum_cost + loc_dif;

			ex -= 1;
		}
		else    //壁だった場合
		{
			right = 99999;
		}

		//どのルートが一番近いか（評価が一番小さい場所）：　同じならreserve_rootにどちらかを保存
		//min_costの初期値をtopに設定
		min_cost = top;
		next_root = E_UP;

		//最小評価より低いかどうか
		if (min_cost > left)
		{
			//低ければmin_costとnext_rootに代入
			min_cost = left;
			next_root = E_LEFT;
		}

		//最小評価より低いかどうか
		if (min_cost > down)
		{
			//低ければmin_costとnext_rootに代入
			min_cost = down;
			next_root = E_DOWN;
		}

		//最小評価より低いかどうか
		if (min_cost > right)
		{
			//低ければmin_costとnext_rootに代入
			min_cost = right;
			next_root = E_RIGHT;
		}

		direction = next_root;

		old_loc = e_sum;

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