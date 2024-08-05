#include "Blinky.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

//�R���X�g���N�^
Blinky::Blinky()
{

}

Blinky::~Blinky()
{

}

void Blinky::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;
}

//void Blinky::PlayerChase(float delta_second)
//{
//
//}

void Blinky::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;

		if (animation_count >= 4)
		{
			image = move_animation[1];

			animation_count = 0;
		}

		image = move_animation[0];

		// �摜�̐ݒ�
		int dir_num = (int)direction;
		if (0 <= dir_num && dir_num < 4)
		{
			eye_image = eye_animation[dir_num];
		}

	}
}