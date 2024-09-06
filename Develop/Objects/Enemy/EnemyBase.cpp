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

	//territory = (-200, -200);

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

	DrawFormatString(10, 10, GetColor(255, 255, 255), "%d", (int)now_mode);
	DrawFormatString(10, 820, GetColor(255, 255, 255), "%.2f, %.2f", territory.x, territory.y);
	DrawFormatString(10, 836, GetColor(255, 255, 255), "%.2f, %.2f", player->GetLocation().x, player->GetLocation().y);

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
	if (hit_object->GetCollision().object_type == eObjectType::wall && collision.is_blocking == true)
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
	if (player->GetPowerUp() && now_mode != START)
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
			//�����꒣���ԂȂ�ǂ��������[�h
			if (now_mode == TERRITORY)
			{
				now_mode = CHASE;

				mode_time = 0;
			}
			else if (now_mode == CHASE) //�����ǂ��������[�h�Ȃ�꒣���ԂɕύX
			{
				now_mode = TERRITORY;

				mode_time = 0;
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

		//�����R���W�����t���b�O���L���Ȃ�
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

	

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += e_velocity * D_ENEMY_SPEED * delta_second;
}

//�J�n������
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
					//�Q�[�g�̈ʒu���W��Y�����ɕϊ�
					int x, y;

					//���݈ʒu��int�^�ɕϊ����ĕۑ�
					int loc_x = (int)location.x;
					int loc_y = (int)location.y;
					/*location.x = 350.0f;
					location.y = 274.0f;*/

					//���݈ʒu��Y�����ɕϊ�
					StageData::ConvertToIndex(gate_point, y, x);

					//���݈ʒu��Y�����ɕϊ�
					StageData::ConvertToIndex(location, ey, ex);

					//�Q�[�g�̂܂ł̈ʒu��T��
					RootSearch(x, y);

					//���݃p�l���̒��S���W���擾
					int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
					int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

					//���݃^�C���̏����擾
					ePanelID panel = StageData::GetPanelData(location);

					//���݃p�l�����Q�[�g�Əd�Ȃ�����
					if (ex == x && ey == y)
					{
						collision.is_blocking = false;

						direction = E_UP;
					}
				}
				else
				{
		
					//�����n�_����o����R���W������L���ɂ���
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
				//�㉺���E�̃p�l�����
				std::map<eAdjacentDirection, ePanelID> panel = {
					{ eAdjacentDirection::UP, ePanelID::NONE },
					{ eAdjacentDirection::DOWN, ePanelID::NONE },
					{ eAdjacentDirection::LEFT, ePanelID::NONE },
					{ eAdjacentDirection::RIGHT, ePanelID::NONE }
				};

				//�㉺���E�̃p�l�����̎擾
				panel = StageData::GetAdjacentPanelData(location);

				//�p�l�����ǈȊO�Ȃ�
				if (panel[eAdjacentDirection::UP] == WALL)
				{
					direction = E_DOWN;
				}

				//�p�l�����ǈȊO�Ȃ�
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
					//�Q�[�g�̈ʒu���W��Y�����ɕϊ�
					int x, y;

					//���݈ʒu��int�^�ɕϊ����ĕۑ�
					int loc_x = (int)location.x;
					int loc_y = (int)location.y;
					/*location.x = 350.0f;
					location.y = 274.0f;*/

					//���݈ʒu��Y�����ɕϊ�
					StageData::ConvertToIndex(gate_point, y, x);

					//���݈ʒu��Y�����ɕϊ�
					StageData::ConvertToIndex(location, ey, ex);

					//�Q�[�g�̂܂ł̈ʒu��T��
					RootSearch(x, y);

					//���݃p�l���̒��S���W���擾
					int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
					int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

					//���݃^�C���̏����擾
					ePanelID panel = StageData::GetPanelData(location);

					//���݃p�l�����Q�[�g�Əd�Ȃ�����
					if (ex == x && ey == y)
					{
						collision.is_blocking = false;

						direction = E_UP;
					}
				}
				else
				{

					//�����n�_����o����R���W������L���ɂ���
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
				//�㉺���E�̃p�l�����
				std::map<eAdjacentDirection, ePanelID> panel = {
					{ eAdjacentDirection::UP, ePanelID::NONE },
					{ eAdjacentDirection::DOWN, ePanelID::NONE },
					{ eAdjacentDirection::LEFT, ePanelID::NONE },
					{ eAdjacentDirection::RIGHT, ePanelID::NONE }
				};

				//�㉺���E�̃p�l�����̎擾
				panel = StageData::GetAdjacentPanelData(location);

				//�p�l�����ǈȊO�Ȃ�
				if (panel[eAdjacentDirection::UP] == WALL)
				{
					direction = E_DOWN;
				}

				//�p�l�����ǈȊO�Ȃ�
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
					//�Q�[�g�̈ʒu���W��Y�����ɕϊ�
					int x, y;

					//���݈ʒu��int�^�ɕϊ����ĕۑ�
					int loc_x = (int)location.x;
					int loc_y = (int)location.y;
					/*location.x = 350.0f;
					location.y = 274.0f;*/

					//���݈ʒu��Y�����ɕϊ�
					StageData::ConvertToIndex(gate_point, y, x);

					//���݈ʒu��Y�����ɕϊ�
					StageData::ConvertToIndex(location, ey, ex);

					//�Q�[�g�̂܂ł̈ʒu��T��
					RootSearch(x, y);

					//���݃p�l���̒��S���W���擾
					int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
					int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

					//���݃^�C���̏����擾
					ePanelID panel = StageData::GetPanelData(location);

					//���݃p�l�����Q�[�g�Əd�Ȃ�����
					if (ex == x && ey == y)
					{
						collision.is_blocking = false;

						direction = E_UP;
					}
				}
				else
				{

					//�����n�_����o����R���W������L���ɂ���
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
				//�㉺���E�̃p�l�����
				std::map<eAdjacentDirection, ePanelID> panel = {
					{ eAdjacentDirection::UP, ePanelID::NONE },
					{ eAdjacentDirection::DOWN, ePanelID::NONE },
					{ eAdjacentDirection::LEFT, ePanelID::NONE },
					{ eAdjacentDirection::RIGHT, ePanelID::NONE }
				};

				//�㉺���E�̃p�l�����̎擾
				panel = StageData::GetAdjacentPanelData(location);

				//�p�l�����ǈȊO�Ȃ�
				if (panel[eAdjacentDirection::UP] == WALL)
				{
					direction = E_DOWN;
				}

				//�p�l�����ǈȊO�Ȃ�
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

//�꒣��Ɍ���������
void EnemyBase::GoTerritory(float delta_second)
{

}

//�v���C���[��ǐՂ��鏈��
void EnemyBase::PlayerChase(float delta_second)
{
	
}

//���X�|�[������
void EnemyBase::EnemyRespawn(float delta_second)
{

}

//���������
void EnemyBase::EnemyEscape(float delta_second)
{
	//���݈ʒu��int�^�ɕϊ����ĕۑ�
	int loc_x = (int)location.x;
	int loc_y = (int)location.y;

	//���݈ʒu��Y�����ɕϊ�
	StageData::ConvertToIndex(location, ey, ex);

	//���݃p�l���̒��S���W���擾
	int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
	int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

	//���S���W�̍��v�l
	int e_sum = ex_center + ey_center;

	//���݃^�C���̏����擾
	ePanelID panel = StageData::GetPanelData(location);

	int random;
	random = GetRand(4);

	//���݃p�l�������S���u�����`�������͌��݃��[�h���X�^�[�g��ԂȂ�i�O����W�Ɠ����Ȃ����Ȃ��j
	if (((loc_x + 1 || loc_x == ex_center && loc_y + 1 || loc_y == ey_center)) && (panel == BRANCH || now_mode == START)
		&& (e_sum != old_loc))
	{
		//�㉺���E�̃p�l�����
		std::map<eAdjacentDirection, ePanelID> panel = {
			{ eAdjacentDirection::UP, ePanelID::NONE },
			{ eAdjacentDirection::DOWN, ePanelID::NONE },
			{ eAdjacentDirection::LEFT, ePanelID::NONE },
			{ eAdjacentDirection::RIGHT, ePanelID::NONE }
		};

		switch (random)
		{
		case 0:
			//�p�l�����ǈȊO�Ȃ�
			if (panel[eAdjacentDirection::UP] != WALL && direction != E_DOWN)
			{
				direction = E_UP;
				break;
			}
		case 1:
			//�p�l�����ǈȊO�Ȃ�
			if (panel[eAdjacentDirection::DOWN] != WALL && direction != E_UP)
			{
				direction = E_DOWN;
				break;
			}

		case 2:
			//�p�l�����ǈȊO�Ȃ�
			if (panel[eAdjacentDirection::LEFT] != WALL && direction != E_RIGHT)
			{
				direction = E_LEFT;
				break;
			}

		case 3:
			//�p�l�����ǈȊO�Ȃ�
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

//�g���l���ʉߌ�������
void EnemyBase::EnemyGate()
{

}

//�ڕW�̃p�l�����W��n���ƍŒZ�����Ō���������
void EnemyBase::RootSearch(int x, int y)
{
	//���݈ʒu��int�^�ɕϊ����ĕۑ�
	int loc_x = (int)location.x;
	int loc_y = (int)location.y;

	//���݈ʒu��Y�����ɕϊ�
	StageData::ConvertToIndex(location, ey, ex);

	//���݃p�l���̒��S���W���擾
	int ex_center = (int)(ex + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;
	int ey_center = (int)(ey + 1) * D_OBJECT_SIZE - D_OBJECT_SIZE / 2;

	//���S���W�̍��v�l
	int e_sum = ex_center + ey_center;

	//���݃^�C���̏����擾
	ePanelID panel = StageData::GetPanelData(location);

	//���݃p�l�������S���u�����`�������͌��݃��[�h���X�^�[�g��ԂȂ�i�O����W�Ɠ����Ȃ����Ȃ��j
	if (((loc_x + 1 || loc_x == ex_center && loc_y + 1 || loc_y == ey_center)) && (panel == BRANCH || now_mode == START)
		&& (e_sum != old_loc))
	{
		//�㉺���E�̃p�l�����
		std::map<eAdjacentDirection, ePanelID> panel = {
			{ eAdjacentDirection::UP, ePanelID::NONE },
			{ eAdjacentDirection::DOWN, ePanelID::NONE },
			{ eAdjacentDirection::LEFT, ePanelID::NONE },
			{ eAdjacentDirection::RIGHT, ePanelID::NONE }
		};

		//float reserve_root[5] = { 9999, 9999, 9999, 9999, 9999 };				//�]���������������ꍇ�Е���ۑ����Ă����z��

		//�㉺���E�̕]���ۑ��z��
		int top = 99999;
		int down = 99999;
		int right = 99999;
		int left = 99999;

		//�]���ۑ��A���[�g�ۑ�
		//int reserve_root[2] = { 99999,99999 };

		//�]���̍��v�l�A�ŏ��l
		int sum_cost = 0;
		int min_cost = 0;

		//���̈ړ�����
		eDirectionState next_root = E_NONE;

		//���݈ʒu�Ɠ꒣��̍�
		int loc_dif = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

		//move_cost = 0;

		//�㉺���E�̃p�l�����̎擾
		panel = StageData::GetAdjacentPanelData(location);

		//�ړ��R�X�g
		//move_cost++;

			//�p�l�����ǈȊO�Ȃ�
		if (panel[eAdjacentDirection::UP] != WALL && direction != E_DOWN)
		{
			ey -= 1;

			//�ړ��R�X�g���ǂ�قǂ��v�Z
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//�]���̕ۑ�
			top = sum_cost + loc_dif;

			ey += 1;
		}
		else    //�ǂ������ꍇ
		{
			top = 99999;
		}

		if (panel[eAdjacentDirection::DOWN] != WALL && direction != E_UP)
		{
			ey += 1;

			//�ړ��R�X�g���ǂ�قǂ��v�Z
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//�]���̕ۑ�
			down = sum_cost + loc_dif;

			ey -= 1;
		}
		else    //�ǂ������ꍇ
		{
			down = 99999;
		}

		if (panel[eAdjacentDirection::LEFT] != WALL && direction != E_RIGHT)
		{
			ex -= 1;

			//�ړ��R�X�g���ǂ�قǂ��v�Z
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//�]���̕ۑ�
			left = sum_cost + loc_dif;

			ex += 1;
		}
		else    //�ǂ������ꍇ
		{
			left = 99999;
		}

		if (panel[eAdjacentDirection::RIGHT] != WALL && direction != E_LEFT)
		{
			ex += 1;

			//�ړ��R�X�g���ǂ�قǂ��v�Z
			sum_cost = ((ex - x) * (ex - x)) + ((ey - y) * (ey - y));

			//�]���̕ۑ�
			right = sum_cost + loc_dif;

			ex -= 1;
		}
		else    //�ǂ������ꍇ
		{
			right = 99999;
		}

		//�ǂ̃��[�g����ԋ߂����i�]������ԏ������ꏊ�j�F�@�����Ȃ�reserve_root�ɂǂ��炩��ۑ�
		//min_cost�̏����l��top�ɐݒ�
		min_cost = top;
		next_root = E_UP;

		//�ŏ��]�����Ⴂ���ǂ���
		if (min_cost > left)
		{
			//�Ⴏ���min_cost��next_root�ɑ��
			min_cost = left;
			next_root = E_LEFT;
		}

		//�ŏ��]�����Ⴂ���ǂ���
		if (min_cost > down)
		{
			//�Ⴏ���min_cost��next_root�ɑ��
			min_cost = down;
			next_root = E_DOWN;
		}

		//�ŏ��]�����Ⴂ���ǂ���
		if (min_cost > right)
		{
			//�Ⴏ���min_cost��next_root�ɑ��
			min_cost = right;
			next_root = E_RIGHT;
		}

		direction = next_root;

		old_loc = e_sum;

	}
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