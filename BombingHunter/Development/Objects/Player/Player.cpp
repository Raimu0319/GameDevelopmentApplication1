#include "Player.h"
#include "../Enemy/Enemy.h"
#include "../../Scene/Scene.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"
#include "Bomb/Bomb.h"

//�R���X�g���N�^
Player::Player() : animation_count(0), filp_flag(FALSE),bomb_SE(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Player::~Player()
{

}

//����������
void Player::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Player/���1.png");
	animation[1] = LoadGraph("Resource/Images/Player/���2.png");

	bomb_SE = LoadSoundMem("Resource/sounds/pan.wav");		//���e�����T�E���h

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("���p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�����蔻��̑傫���ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�I�u�W�F�N�g�̃^�C�v
	type = PLAYER;

	//�����������Ȃ���
	Check_active = TRUE;

	//�ړ��̑���
	velocity = 0.0f;

	//���e�̐������
	bomb_stop = 0;
}

//�X�V����
void Player::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimetionControl();

	//�X�y�[�X�L�[����������A���e�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		if (bomb_stop == 0)
		{	
			PlaySoundMem(bomb_SE, DX_PLAYTYPE_BACK,TRUE);		//SE�̍Đ�
			CreateObject<Bomb>(Vector2D(this->location.x, this->location.y))->SetDirection(this->velocity);
		}
	}
}

//�`�揈��
void Player::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);
}

//�I��������
void Player::Finalize()
{
	//�g�p�����摜��SE���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteSoundMem(bomb_SE);
}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object)
{
	
}

//�ړ�����
void Player::Movement()
{
	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x = -1.0f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = 1.0f;
		filp_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//��ʊO�ɂ����Ȃ��悤�ɐ�������
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if ((640.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 640.0f - (box_size.x / 2.0f);
	}

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void Player::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�A�j���[�V��������
void Player::AnimetionControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}