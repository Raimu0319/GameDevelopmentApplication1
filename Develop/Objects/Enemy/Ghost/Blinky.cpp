#include "Blinky.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

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
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	//�G�l�~�[�^�C�v�ݒ�
	enemy_type = BLINKY;

	now_mode = TERRITORY;

	direction = E_RIGHT;

	//�꒣��ݒ�
	territory.x = 550.0f;
	territory.y = 1.0f;

	//�����摜�̐ݒ�
	image = move_animation[0];

	// �����̐ݒ�
	mobility = eMobilityType::Movable;
}

//void Blinky::PlayerChase(float delta_second)
//{
//	//���݈ʒu��int�^�ɕϊ����ĕۑ�
//	int loc_x = (int)location.x;
//	int loc_y = (int)location.y;
//
//	//���݈ʒu��Y�����ɕϊ�
//	::ConvertToIndex(location, ey, ex);
//
//	//���݃p�l���̒��S���W���擾
//	int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
//	int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
//
//	//���S���W�̍��v�l
//	int e_sum = ex_center + ey_center;
//
//	//���݃^�C���̏����擾
//	ePanelID panel = StageData::GetPanelData(location);
//
//	//���݃p�l�����u�����`���O����W�Ɠ����ł͂Ȃ����
//	if (((loc_x == ex_center && loc_y == ey_center || ey_center - 1)) && panel == BRANCH
//		&& (e_sum != old_loc))
//	{
//
//		//�꒣��̍��W��Y�����ɕϊ�
//		StageData::ConvertToIndex(player->GetLocation(), py, px);
//
//		//�㉺���E�̃p�l�����
//		std::map<eAdjacentDirection, ePanelID> panel = {
//			{ eAdjacentDirection::UP, ePanelID::NONE },
//			{ eAdjacentDirection::DOWN, ePanelID::NONE },
//			{ eAdjacentDirection::LEFT, ePanelID::NONE },
//			{ eAdjacentDirection::RIGHT, ePanelID::NONE }
//		};
//
//		//float reserve_root[5] = { 9999, 9999, 9999, 9999, 9999 };				//�]���������������ꍇ�Е���ۑ����Ă����z��
//
//		//�㉺���E�̕]���ۑ��z��
//		int top = 99999;
//		int down = 99999;
//		int right = 99999;
//		int left = 99999;
//
//		//�]���ۑ��A���[�g�ۑ�
//		//int reserve_root[2] = { 99999,99999 };
//
//		//�]���̍��v�l�A�ŏ��l
//		int sum_cost = 0;
//		int min_cost = 0;
//
//		//���̈ړ�����
//		eDirectionState next_root = E_NONE;
//
//		//���݈ʒu�Ɠ꒣��̍�
//		int loc_dif = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//		//move_cost = 0;
//
//		//�㉺���E�̃p�l�����̎擾
//		panel = StageData::GetAdjacentPanelData(location);
//
//		//�ړ��R�X�g
//		//move_cost++;
//
//			//�p�l�����ǈȊO�Ȃ�
//		if (panel[eAdjacentDirection::UP] != WALL && direction != E_DOWN)
//		{
//			ey -= 1;
//
//			//�ړ��R�X�g���ǂ�قǂ��v�Z
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//�]���̕ۑ�
//			top = sum_cost + loc_dif;
//
//			ey += 1;
//		}
//		else    //�ǂ������ꍇ
//		{
//			top = 99999;
//		}
//
//		if (panel[eAdjacentDirection::DOWN] != WALL && direction != E_UP)
//		{
//			ey += 1;
//
//			//�ړ��R�X�g���ǂ�قǂ��v�Z
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//�]���̕ۑ�
//			down = sum_cost + loc_dif;
//
//			ey -= 1;
//		}
//		else    //�ǂ������ꍇ
//		{
//			down = 99999;
//		}
//
//		if (panel[eAdjacentDirection::LEFT] != WALL && direction != E_RIGHT)
//		{
//			ex -= 1;
//
//			//�ړ��R�X�g���ǂ�قǂ��v�Z
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//�]���̕ۑ�
//			left = sum_cost + loc_dif;
//
//			ex += 1;
//		}
//		else    //�ǂ������ꍇ
//		{
//			left = 99999;
//		}
//
//		if (panel[eAdjacentDirection::RIGHT] != WALL && direction != E_LEFT)
//		{
//			ex += 1;
//
//			//�ړ��R�X�g���ǂ�قǂ��v�Z
//			sum_cost = ((ex - px) * (ex - px)) + ((ey - py) * (ey - py));
//
//			//�]���̕ۑ�
//			right = sum_cost + loc_dif;
//
//			ex -= 1;
//		}
//		else    //�ǂ������ꍇ
//		{
//			right = 99999;
//		}
//
//		//�ǂ̃��[�g����ԋ߂����i�]������ԏ������ꏊ�j�F�@�����Ȃ�reserve_root�ɂǂ��炩��ۑ�
//		//min_cost�̏����l��top�ɐݒ�
//		min_cost = top;
//		next_root = E_UP;
//
//		//�ŏ��]�����Ⴂ���ǂ���
//		if (min_cost > left)
//		{
//			//�Ⴏ���min_cost��next_root�ɑ��
//			min_cost = left;
//			next_root = E_LEFT;
//		}
//
//		//�ŏ��]�����Ⴂ���ǂ���
//		if (min_cost > down)
//		{
//			//�Ⴏ���min_cost��next_root�ɑ��
//			min_cost = down;
//			next_root = E_DOWN;
//		}
//
//		//�ŏ��]�����Ⴂ���ǂ���
//		if (min_cost > right)
//		{
//			//�Ⴏ���min_cost��next_root�ɑ��
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
	// �ړ����̃A�j���[�V����
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

			// �摜�̐ݒ�
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