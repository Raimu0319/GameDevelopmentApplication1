#include "../../Scene/Scene.h"
#include "hakoteki.h"
#include "Enemy.h"
#include "DxLib.h"

//�R���X�g���N�^
Hakoteki::Hakoteki() : animation_count(0), direction(0.0f)
{
	hakoteki[0] = NULL;
	hakoteki[1] = NULL;
}	

//�f�X�g���N�^
Hakoteki::~Hakoteki()
{

}

//����������
void Hakoteki::Initialize()
{
	int i;

	//�摜�̓ǂݍ���
	hakoteki[0] = LoadGraph("Resource/Images/Enemy/hakoteki1.png");
	hakoteki[1] = LoadGraph("Resource/Images/Enemy/hakoteki2.png");
	
	//�G���[�`�F�b�N
	for (i = 0; i < 2; i++)
	{
		if (hakoteki[i] == -1)
		{
			throw("�n�R�e�L�摜������܂���\n");
		}
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 40.0f;

	image = hakoteki[0];

	//�����摜�̐ݒ�
	RandomSpwan();

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	type = enemy;

	//�\�����邩���Ȃ���
	Check_active = TRUE;
}

//�X�V����
void Hakoteki::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimetionControl();

}

//�`�揈��
void Hakoteki::Draw() const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
	/*
	//�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.6, 0.0, image, TRUE);

	Vector2D upper_left = location - (box_size / 2.0f);
	Vector2D lower_right = location + (box_size / 2.0f);

	//�����蔻��̉���
	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y, GetColor(255, 0, 0), FALSE);
	*/
}

//�I��������
void Hakoteki::Finalize()
{
	int i;

	for (i = 0; i < 2; i++)
	{
		DeleteGraph(hakoteki[i]);
	}

}

//�����蔻��ʒm����
void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	//�G���m���G�ꂽ�ꍇ
	if (hit_object->get_type() != enemy)
	{
		//�����������ɍs������
		direction = 0.0f;

		Check_active = FALSE;
	}

}

//�ʒu���擾����
Vector2D Hakoteki::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void Hakoteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�ړ�����
void Hakoteki::Movement()
{
	//��ʉE�[�ɓ��B������A���[�ɖ߂�
	//if (((location.x + direction.x) < box_size.x) ||(640.0f - box_size.x) < (location.x + direction.x))
	if ((640.0f - box_size.x) < (location.x + direction.x))
	{
		location.x = -1.0f;
		direction.x *= 1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(480.0f - box_size.y) < (location.y + direction.y))
	{
		location.x = 630;
		direction.y *= -1.0f;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�G�A�j���[�V��������
void Hakoteki::AnimetionControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//count�̃��Z�b�g
		animation_count = 0;


		//�摜�̐؂�ւ�
		if (image == hakoteki[0])
		{
			image = hakoteki[1];
		}
		else if (image == hakoteki[1])
		{
			image = hakoteki[0];
		}

	}
}