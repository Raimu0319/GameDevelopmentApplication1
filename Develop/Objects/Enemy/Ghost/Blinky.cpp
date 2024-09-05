#include "Blinky.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//コンストラクタ
Blinky::Blinky()
{

}

Blinky::~Blinky()
{

}

void Blinky::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	//エネミータイプ設定
	enemy_type = BLINKY;

	now_mode = TERRITORY;

	direction = E_RIGHT;

	//縄張り設定
	territory.x = 550.0f;
	territory.y = 1.0f;

	//初期画像の設定
	image = move_animation[0];

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

//void Blinky::PlayerChase(float delta_second)
//{
//	//現在位置をint型に変換して保存
//	int loc_x = (int)location.x;
//	int loc_y = (int)location.y;
//
//	//現在位置を添え字に変換
//	::ConvertToIndex(location, ey, ex);
//
//	//現在パネルの中心座標を取得
//	int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
//	int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
//
//	//中心座標の合計値
//	int e_sum = ex_center + ey_center;
//
//	//現在タイルの情報を取得
//	ePanelID panel = StageData::GetPanelData(location);
//
//	//現在パネルがブランチかつ前回座標と同じではなければ
//	if (((loc_x == ex_center && loc_y == ey_center || ey_center - 1)) && panel == BRANCH
//		&& (e_sum != old_loc))
//	{
//
//		//縄張りの座標を添え字に変換
//		StageData::ConvertToIndex(player->GetLocation(), py, px);
//
//		//上下左右のパネル情報
//		std::map<eAdjacentDirection, ePanelID> panel = {
//			{ eAdjacentDirection::UP, ePanelID::NONE },
//			{ eAdjacentDirection::DOWN, ePanelID::NONE },
//			{ eAdjacentDirection::LEFT, ePanelID::NONE },
//			{ eAdjacentDirection::RIGHT, ePanelID::NONE }
//		};
//
//		//float reserve_root[5] = { 9999, 9999, 9999, 9999, 9999 };				//評価が同じだった場合片方を保存しておく配列
//
//		//上下左右の評価保存配列
//		int top = 99999;
//		int down = 99999;
//		int right = 99999;
//		int left = 99999;
//
//		//評価保存、ルート保存
//		//int reserve_root[2] = { 99999,99999 };
//
//		//評価の合計値、最小値
//		int sum_cost = 0;
//		int min_cost = 0;
//
//		//次の移動方向
//		eDirectionState next_root = E_NONE;
//
//		//現在位置と縄張りの差
//		int loc_dif = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//		//move_cost = 0;
//
//		//上下左右のパネル情報の取得
//		panel = StageData::GetAdjacentPanelData(location);
//
//		//移動コスト
//		//move_cost++;
//
//			//パネルが壁以外なら
//		if (panel[eAdjacentDirection::UP] != WALL && direction != E_DOWN)
//		{
//			ey -= 1;
//
//			//移動コストがどれほどか計算
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//評価の保存
//			top = sum_cost + loc_dif;
//
//			ey += 1;
//		}
//		else    //壁だった場合
//		{
//			top = 99999;
//		}
//
//		if (panel[eAdjacentDirection::DOWN] != WALL && direction != E_UP)
//		{
//			ey += 1;
//
//			//移動コストがどれほどか計算
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//評価の保存
//			down = sum_cost + loc_dif;
//
//			ey -= 1;
//		}
//		else    //壁だった場合
//		{
//			down = 99999;
//		}
//
//		if (panel[eAdjacentDirection::LEFT] != WALL && direction != E_RIGHT)
//		{
//			ex -= 1;
//
//			//移動コストがどれほどか計算
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//評価の保存
//			left = sum_cost + loc_dif;
//
//			ex += 1;
//		}
//		else    //壁だった場合
//		{
//			left = 99999;
//		}
//
//		if (panel[eAdjacentDirection::RIGHT] != WALL && direction != E_LEFT)
//		{
//			ex += 1;
//
//			//移動コストがどれほどか計算
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//評価の保存
//			right = sum_cost + loc_dif;
//
//			ex -= 1;
//		}
//		else    //壁だった場合
//		{
//			right = 99999;
//		}
//
//		//どのルートが一番近いか（評価が一番小さい場所）：　同じならreserve_rootにどちらかを保存
//		//min_costの初期値をtopに設定
//		min_cost = top;
//		next_root = E_UP;
//
//		//最小評価より低いかどうか
//		if (min_cost > left)
//		{
//			//低ければmin_costとnext_rootに代入
//			min_cost = left;
//			next_root = E_LEFT;
//		}
//
//		//最小評価より低いかどうか
//		if (min_cost > down)
//		{
//			//低ければmin_costとnext_rootに代入
//			min_cost = down;
//			next_root = E_DOWN;
//		}
//
//		//最小評価より低いかどうか
//		if (min_cost > right)
//		{
//			//低ければmin_costとnext_rootに代入
//			min_cost = right;
//			next_root = E_RIGHT;
//		}
//
//		direction = next_root;
//
//		old_loc = e_sum;
//
//	}
//}

void Blinky::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		if (now_mode != IZIKE)
		{

			animation_time = 0.0f;
			animation_count++;

			if (animation_count >= 6)
			{
				if (image == move_animation[0])
				{
					image = move_animation[1];
				}
				else
				{
					image = move_animation[0];
				}
				animation_count = 0;
			}

			// 画像の設定
			int dir_num = (int)direction;
			if (0 <= dir_num && dir_num < 4)
			{
				eye_image = eye_animation[dir_num];
			}
		}
		else if (now_mode == IZIKE)
		{
			animation_time = 0.0f;
			animation_count++;

			if (animation_count >= 8)
			{
				if (image == move_animation[16])
				{
					image = move_animation[17];
				}
				else
				{
					image = move_animation[16];
				}

				animation_count = 0;
			}

		}
		
	}
}