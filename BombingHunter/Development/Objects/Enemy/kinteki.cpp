#include "../../Scene/Scene.h"
#include "kinteki.h"
#include "Enemy.h"
#include "DxLib.h"

//�R���X�g���N�^
Kinteki::Kinteki() : animation_count(0), direction(0.0f)
{
	kinteki[0] = NULL;
	kinteki[1] = NULL;
	kinteki[2] = NULL;
	kinteki[3] = NULL;
	kinteki[4] = NULL;
}

//�f�X�g���N�^
Kinteki::~Kinteki()
{

}

//����������
void Kinteki::Initialize()
{
	int i;

	//�摜�̓ǂݍ���
	kinteki[0] = LoadGraph("Resource/Images/Enemy/kinteki.png");
	kinteki[1] = LoadGraph("Resource/Images/Enemy/kinteki1.png");
	kinteki[2] = LoadGraph("Resource/Images/Enemy/kinteki2.png");
	kinteki[3] = LoadGraph("Resource/Images/Enemy/kinteki3.png");
	kinteki[4] = LoadGraph("Resource/Images/Enemy/kinteki4.png");

	//�G���[�`�F�b�N
	for (i = 0; i < 5; i++)
	{
		if (kinteki[i] == -1)
		{
			throw("�L���e�L�̉摜������܂���\n");
		}
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 32.0f;

	image = kinteki[0];

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
void Kinteki::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimetionControl();

}

//�`�揈��
void Kinteki::Draw() const
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
void Kinteki::Finalize()
{
	int i;

	for (i = 0; i < 5; i++)
	{
		DeleteGraph(kinteki[i]);
	}

}

//�����蔻��ʒm����
void Kinteki::OnHitCollision(GameObject* hit_object)
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
Vector2D Kinteki::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void Kinteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�ړ�����
void Kinteki::Movement()
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
void Kinteki::AnimetionControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == kinteki[0])
		{
			image = kinteki[1];
		}
		else if (image == kinteki[1])
		{
			image = kinteki[2];
		}
		else if (image == kinteki[2])
		{
			image = kinteki[3];
		}
		else if (image == kinteki[3])
		{
			image = kinteki[4];
		}
		else if (image == kinteki[4])
		{
			image = kinteki[0];
		}

	}
}