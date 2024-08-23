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

//����������
void EnemyBase::Initialize()
{
	//now_mode;					//���݂̏��
	//move_animation;		//�S�[�X�g�摜
	//eye_animation;		//�ڂ̉摜
	//direction;			//�i�s����
	//e_velocity;				//�ړ����x
	//start_point;			//�����n�_�̍��W

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

}

//�X�V����
void EnemyBase::Update(float delta_second)
{
	//�ړ�����
	Movement(delta_second);

	ModeChange(delta_second);

	//�A�j���[�V��������
	AnimationControl(delta_second);

	
	old_direction = direction;
}

//�`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	if (now_mode != IZIKE)
	{
		// �I�t�Z�b�g�l����ɃG�l�~�[�̖ډ摜�̕`����s��
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}

}

//�I��������
void EnemyBase::Finalize()
{
	move_animation.clear();		//�S�[�X�g�摜
	eye_animation.clear();		//�ڂ̉摜
}

//�v���C���[�̃|�C���^���擾
void EnemyBase::GetPlayerpointer(Player* player)
{
	this->player = player;
}

//�����蔻��ʒm����
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}
}

//��ԕύX����
void EnemyBase::ModeChange(float delta_second)
{
	//�v���C���[���p���[�A�b�v��Ԃ������ꍇ�C�W�P��ԂɂȂ�
	if (player->GetPowerUp())
	{
		now_mode = IZIKE;
	}
	
	//���ݏ�Ԃ��C�W�P��ԂȂ�
	if (now_mode == IZIKE)
	{
		now_time += delta_second;
		if (now_time >= (1.0f / 16.0f))
		{
			now_time = 0.0f;
			izke_time++;
			//��莞�Ԍo�߂�����v���C���[�̃p���[�������ă��[�h��߂��B
			if (izke_time >= 40)
			{
				now_mode = CHASE;
				player->SetPowerDown();
				izke_time = 0.0f;
			}
		}
	}
}

//�ړ�����
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

	// �ړ������Ɉړ����Ă��Ȃ���� direction_state ��ύX����
	switch (direction)
	{
	case eDirectionState::E_UP:
	case eDirectionState::E_DOWN:
	{
		float diff = location.y - old_location.y;
		if (((direction == eDirectionState::E_UP) && (diff < 0.0f)) ||
			((direction == eDirectionState::E_DOWN) && (0.0f < diff)))
		{
			// �ړ������Ɉړ����Ă�̂� break
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
			// �ړ������Ɉړ����Ă�̂� break
			break;
		}

		e_velocity.x = 0.0f;
	}
	break;

	default:// �������Ȃ�
		break;
	}

	// �i�s�����̈ړ��ʂ�ǉ�
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

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += e_velocity * D_ENEMY_SPEED * delta_second;
}

//�J�n������
void EnemyBase::EnemyStart(float delta_second)
{

}

//�꒣��Ɍ���������
void EnemyBase::GoTerritory(float delta_second)
{
	switch (enemy_type)
	{
	case BLINKY:
	{
		// ���݃p�l���̏�Ԃ��m�F
		ePanelID panel = StageData::GetPanelData(location);

		//���݃p�l�����u�����`�Ȃ�
		if (panel == BRANCH)
		{
			//�㉺���E�̃p�l�����
			std::map<eAdjacentDirection, ePanelID> panel = {
				{ eAdjacentDirection::UP, ePanelID::NONE },
				{ eAdjacentDirection::DOWN, ePanelID::NONE },
				{ eAdjacentDirection::LEFT, ePanelID::NONE },
				{ eAdjacentDirection::RIGHT, ePanelID::NONE }
			};

			//���[�g�ۑ�
			std::vector<std::vector<float>> root;

			//�㉺���E�̃p�l�����̎擾
			panel = StageData::GetAdjacentPanelData(location);

			//�v�Z���������@F = H + G (H::�v���C���[�ƃG�l�~�[�̋��� G::���݈ʒu���牽�񓮂���)
			loc_diff = territory - location;

			//�T�����I�����Ă��邩�ǂ���
			while (search_end == false)
			{
				//�ړ��R�X�g
				move_cost += 1.0f;

				//�p�l�����ǈȊO�Ȃ�
				if (panel[eAdjacentDirection::UP] != WALL)
				{
					//�ړ��R�X�g���ǂ�قǂ��v�Z
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

				//���݈ʒu���꒣��Ƌ߂�������
				if (location.x == territory.x && location.y == territory.y)
				{
					search_end = true;
				}
				
			}

			//if (panel[eAdjacentDirection::UP] != WALL)
			//{			
			//	//�i�s�����Ƌt�̕����ɐi�܂Ȃ��悤�ɂ���
			//	if (old_direction != E_DOWN)
			//	{
			//		direction = E_UP;
			//	}

			//	//F�̒l����ԏ��������Ɍ������ē���
			//}

			//if (panel[eAdjacentDirection::DOWN] != WALL)
			//{
			//	//�i�s�����Ƌt�̕����ɐi�܂Ȃ��悤�ɂ���
			//	if (old_direction != E_UP)
			//	{
			//		direction = E_DOWN;
			//	}
			//	
			//}

			//if (panel[eAdjacentDirection::LEFT] != WALL)
			//{
			//	//�i�s�����Ƌt�̕����ɐi�܂Ȃ��悤�ɂ���
			//	if (old_direction != E_RIGHT)
			//	{
			//		direction = E_LEFT;
			//	}

			//}

			//if (panel[eAdjacentDirection::RIGHT] != WALL)
			//{
			//	//�i�s�����Ƌt�̕����ɐi�܂Ȃ��悤�ɂ��還
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

//�v���C���[��ǐՂ��鏈��
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

//���X�|�[������
void EnemyBase::EnemyRespawn(float delta_second)
{

}

//���������
void EnemyBase::EnemyEscape(float delta_second)
{

}

//�g���l���ʉߌ�������
void EnemyBase::EnemyGate()
{

}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
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

	//	// �摜�̐ݒ�
	//	int dir_num = (int)direction;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		eye_image = eye_animation[dir_num];
	//	}

	//}
}