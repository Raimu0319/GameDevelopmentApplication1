#include "Inky.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

//コンストラクタ
Inky::Inky()
{

}

Inky::~Inky()
{

}

void Inky::Initialize()
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
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	//エネミータイプ設定
	enemy_type = INKY;

	//初期画像の設定
	image = move_animation[6];

	territory.x = 670.0f;
	territory.y = 860.0f;

	// 可動性の設定
	mobility = eMobilityType::Movable;
}

//void Blinky::PlayerChase(float delta_second)
//{
//
//}

void Inky::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;

		if (animation_count >= 6)
		{
			if (image == move_animation[6])
			{
				image = move_animation[7];
			}
			else
			{
				image = move_animation[6];
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
}