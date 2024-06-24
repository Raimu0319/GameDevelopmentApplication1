#include "../../Scene/Scene.h"
#include "Haneteki.h"
#include "DxLib.h"

//�R���X�g���N�^
Haneteki::Haneteki()
{
	haneteki[0] = NULL;
	haneteki[1] = NULL;

	happy[0] = NULL;
	happy[1] = NULL;
}

//�f�X�g���N�^
Haneteki::~Haneteki()
{

}

//����������
void Haneteki::Initialize()
{
	int i;

	//�摜�̓ǂݍ���
	haneteki[0] = LoadGraph("Resource/Images/Enemy/haneteki1.png");
	haneteki[1] = LoadGraph("Resource/Images/Enemy/haneteki2.png");

	happy[0] = LoadGraph("Resource/Images/Enemy/happy1.png");
	happy[1] = LoadGraph("Resource/Images/Enemy/happy2.png");

	//�G���[�`�F�b�N
	for (i = 0; i < 2; i++)
	{
		if (haneteki[i] == -1)
		{
			throw("�n�l�e�L�̉摜������܂���\n");
		}

		if (happy[i] == -1)
		{
			throw("�n�[�s�B�̉摜������܂���\n");
		}
	}

	//�����i�s�����̐ݒ�
	__super::Initialize();

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 40.0f;

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	type = ENEMY;

	//�\�����邩���Ȃ���
	Check_active = TRUE;
	
	//�n�l�e�L���n�[�s�B��
	RandomSpwan();

	//�X�R�A�ݒ�
	if (image == haneteki[0] || image == haneteki[1])
	{
		score = 30;
	}
	else
	{
		score = -100;
	}
}

//�X�V����
void Haneteki::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimetionControl();
}

//�`�揈��
void Haneteki::Draw() const
{

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
	
}

//�I��������
void Haneteki::Finalize()
{
	int i;

	//�g�p�����摜���J��
	for (i = 0; i < 2; i++)
	{
		DeleteGraph(haneteki[i]);
		DeleteGraph(happy[i]);
	}
}

//�����蔻��ʒm����
void Haneteki::OnHitCollision(GameObject* hit_object)
{
	//�G���m���G�ꂽ�ꍇ
	if (hit_object->get_type() != ENEMY)
	{
		//�����������ɍs������
		direction = 0.0f;

		Check_active = FALSE;
	}
}


void Haneteki::RandomSpwan()
{
	int i;
	i = GetRand(5);

	switch (i)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		image = haneteki[0];
		break;

	case 4:
	case 5:
		image = happy[0];
		break;
	}
}


//�ʒu���擾����
Vector2D Haneteki::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void Haneteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�ړ�����
void Haneteki::Movement()
{
	__super::Movement();
}

//�G�A�j���[�V��������
void Haneteki::AnimetionControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == haneteki[0])
		{
			image = haneteki[1];
		}
		else if (image == haneteki[1])
		{
			image = haneteki[0];
		}

		if (image == happy[0])
		{
			image = happy[1];
		}
		else if (image == happy[1])
		{
			image = happy[0];
		}
	}
}