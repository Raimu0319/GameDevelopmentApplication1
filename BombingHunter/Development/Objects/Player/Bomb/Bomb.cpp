#include "Bomb.h"
#include "../../Scene/Scene.h"
#include "BombEffect.h"
#include "../Player.h"
#include "DxLib.h"
#include <math.h>

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0), filp_flag(FALSE), explosion_SE(NULL),player(nullptr)
{
	bomb_img = NULL;
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	bomb_img = LoadGraph("Resource/Images/Bomb/Bomb.png");

	explosion_SE = LoadSoundMem("Resource/sounds/explosion.wav");		//���e�����T�E���h
	
	//�G���[�`�F�b�N
	if (bomb_img == -1)
	{
		throw("���e�̉摜������܂���\n");
	}
	
	//�����̐ݒ�
	radian = DX_PI / 2.0;

	//�����蔻��̑傫���ݒ�
	box_size = 54.0;

	//�����摜�̐ݒ�
	image = bomb_img;

	//�I�u�W�F�N�g�̃^�C�v
	type = BOMB;

	//�\�����邩���Ȃ���
	Check_active = TRUE;

	//�����x�̏����ݒ�
	direction = 0;	
}

//�X�V����
void Bomb::Update()
{
	//�ړ�����
	Movement();
}

//�`�揈��
void Bomb::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);
}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜��SE���������
	DeleteGraph(bomb_img);
	DeleteSoundMem(explosion_SE);
}

void Bomb::GetPlayerpoint(Player* player)
{
	this->player = player;
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//���������I�u�W�F�N�g���G�������ꍇ
	if (hit_object->get_type() == ENEMY)
	{
		location.y += direction.y;

		//�����蔻��̍폜
		box_size = 0.0;

		//���̃I�u�W�F�N�g������
		Check_active = FALSE;

		//SE�̍Đ�
		PlaySoundMem(explosion_SE,DX_PLAYTYPE_BACK,TRUE);

		//�G�t�F�N�g�̐���
		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
	}
}
 
void Bomb::SetDirection(Vector2D P_velocity)
{
	//�v���C���[���ړ����Ȃ��甚�e�𐶐�������
	if (P_velocity.x == 0.0f)
	{
		//�܂��������ɗ����Ă���
		direction.y = 2.0f;
		direction_add.y = 0.0f;
	}
	else if (P_velocity.x > 0)
	{
		//�v���C���[�̐i�s�����ɉ����Ăӂ���Ɨ����Ă���
		direction.x = P_velocity.x;
		direction_add.y = 0.02f;

		//���e�̊p�x����
		radian = atan2f(direction.y, direction.x);							//��/�������ă��W�A�����v�Z����

		filp_flag = FALSE;
	}
	else
	{
		//�v���C���[�̐i�s�����ɉ����Ăӂ���Ɨ����Ă���
		direction.x = P_velocity.x;
		direction_add.y = 0.02f;
		//Vector2D B_dire = direction;

		//���e�̊p�x����
		radian = atan2f(direction.y, direction.x);							//��/�������ă��W�A�����v�Z����

		filp_flag = FALSE;
	}
}

//�ړ�����
void Bomb::Movement()
{
	//���e����ʊO�ɓ��B�����Ƃ��̏����@
	if (location.y > 380.0f)
	{
		direction.y = 0.0f;

		this->Check_active = FALSE;

		//SE�̍Đ�
		PlaySoundMem(explosion_SE, DX_PLAYTYPE_BACK, TRUE);

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
	}

	//��ʊO�ɏo�Ȃ��悤�ɂ��鏈��
	if ((640.0f - (box_size.x / 2)) < (location.x) || location.x < (box_size.x / 2))
	{
		direction.x = 0.0f;
	}

	//��ʏ�ɓ��B������A�폜����
	if (location.y < 0)
	{
		this->Check_active = FALSE;

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
	}

	//�����鑬�x��2.0f�ȉ��̏ꍇ�ǂ�ǂ�������Ă���
	if (direction.y <= 2.0f)
	{
		direction.y += direction_add.y;
	}
	
	//���e�̌�����ς��鏈��
	if (radian != DX_PI / 2.0)
	{
		if (DX_PI / 2.0 < radian)
		{
			radian -= ((DX_PI / 2.0) - radian) / -80;
		}
		else
		{
			radian += ((DX_PI / 2.0) - radian) / 80;
		}
	}

	//���݂̈ʒu���W�ɑ��������Z����
	location += direction;
}