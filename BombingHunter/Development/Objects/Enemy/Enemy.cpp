#include "../../Scene/Scene.h"
#include "Enemy.h"
#include "DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	hakoteki[0] = NULL;
	hakoteki[1] = NULL;

	haneteki[0] = NULL;
	haneteki[1] = NULL;

	happy[0] = NULL;
	happy[1] = NULL;

	kinteki[0] = NULL;
	kinteki[1] = NULL;
	kinteki[2] = NULL;
	kinteki[3] = NULL;
	kinteki[4] = NULL;

}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	int i;

	//�摜�̓ǂݍ���
	hakoteki[0] = LoadGraph("Resource/Images/Enemy/hakoteki1.png");
	hakoteki[1] = LoadGraph("Resource/Images/Enemy/hakoteki2.png");

	haneteki[0] = LoadGraph("Resource/Images/Enemy/haneteki1.png");
	haneteki[1] = LoadGraph("Resource/Images/Enemy/haneteki2.png");

	happy[0] = LoadGraph("Resource/Images/Enemy/happy1.png");
	happy[1] = LoadGraph("Resource/Images/Enemy/happy2.png");

	kinteki[0] = LoadGraph("Resource/Images/Enemy/kinteki.png");
	kinteki[1] = LoadGraph("Resource/Images/Enemy/kinteki1.png");
	kinteki[2] = LoadGraph("Resource/Images/Enemy/kinteki2.png");
	kinteki[3] = LoadGraph("Resource/Images/Enemy/kinteki3.png");
	kinteki[4] = LoadGraph("Resource/Images/Enemy/kinteki4.png");

	//�G���[�`�F�b�N
	for (i = 0; i < 2; i++)
	{
		if (hakoteki[i] == -1)
		{
			throw("�n�R�e�L�̉摜������܂���\n");
		}

		if (haneteki[i] == -1)
		{
			throw("�n�l�e�L�̉摜������܂���\n");
		}

		if (happy[i] == -1)
		{
			throw("�n�[�s�B�̉摜������܂���\n");
		}

	}

	for (i = 0; i < 5; i++)
	{
		if (hakoteki[i] == -1)
		{
			throw("�L���e�L�̉摜������܂���\n");
		}
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	image = NULL;

	//�����摜�̐ݒ�
	RandomSpwan();

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);

	type = enemy;
}

//�X�V����
void Enemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimetionControl();

}

//�`�揈��
void Enemy::Draw() const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//������Ƀn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

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
void Enemy::Finalize()
{
	int i;

	//�g�p�����摜���J��
	for (i = 0; i < 2; i++)
	{
		DeleteGraph(hakoteki[i]);
		DeleteGraph(haneteki[i]);
		DeleteGraph(happy[i]);
	}

	for (i = 0; i < 4; i++)
	{
		DeleteGraph(kinteki[i]);
	}


}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//�G���m���G�ꂽ�ꍇ
	if (hit_object->get_type() != enemy)
	{
		//�����������ɍs������
		direction = 0.0f;
	}	
	
}

//�ʒu���擾����
Vector2D Enemy::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void Enemy::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�ړ�����
void Enemy::Movement()
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

void Enemy::RandomSpwan()
{
	int i;
	i =  GetRand(6);

	switch (i)
	{
	case 0:
	case 1:
	case 2:
		image = hakoteki[0];
		break;
	
	case 3:
	case 4:
		image = haneteki[0];
		break;

	case 5:
		image = happy[0];
		break;

	case 6:
		image = kinteki[0];
		break;

	}
}

//�G�A�j���[�V��������
void Enemy::AnimetionControl()
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

		if (image == haneteki[0])
		{
			image = haneteki[1];
		}
		else if(image == haneteki[1])
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