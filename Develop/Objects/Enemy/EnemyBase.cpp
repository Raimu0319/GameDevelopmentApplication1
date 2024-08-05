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

//����������
void EnemyBase::Initialize()
{
	now_mode;					//���݂̏��
	move_animation;		//�S�[�X�g�摜
	eye_animation;		//�ڂ̉摜
	direction;			//�i�s����
	e_velocity;				//�ړ����x
	territory;					//�꒣����W
	start_point;			//�����n�_�̍��W

	player = nullptr;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

}

//�X�V����
void EnemyBase::Update(float delta_second)
{
	//��Ԑ؂�ւ�
	ModeChange();

	//�ړ�����
	Movement(delta_second);

	//�A�j���[�V��������
	AnimationControl(delta_second);
}

//�`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	// �I�t�Z�b�g�l����ɃG�l�~�[�̖ډ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
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

}

//��ԕύX����
void EnemyBase::ModeChange()
{
	//�v���C���[���p���[�A�b�v��Ԃ������ꍇ�C�W�P��ԂɂȂ�
	/*if (player->GetPowerUp())
	{
		now_mode = IZIKE;
	}*/
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
}

//�J�n������
void EnemyBase::EnemyStart(float delta_second)
{

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

}

//�g���l���ʉߌ�������
void EnemyBase::EnemyGate()
{

}

//�G�L������������
void EnemyBase::EnemyCreate(int enemycreate_court)
{
	if (enemycreate_court == 0)
	{
		CreateObject<Blinky>(location);
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
	//		image = animation_num[1];

	//		animation_count = 0;
	//	}

	//	image = animation_num[0];

	//	// �摜�̐ݒ�
	//	int dir_num = (int)direction;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		eye_image = eye_animation[dir_num];
	//	}

	//}
}