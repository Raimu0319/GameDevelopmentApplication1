#include "../../Scene/Scene.h"
#include "Enemy.h"
#include "DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	
}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	
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
		flip_flag = TRUE;
	}
	else
	{
		flip_flag = FALSE;
	}

	//������ɓG�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
	
}

//�I��������
void Enemy::Finalize()
{
	//int i;

	////�g�p�����摜���J��
	//for (i = 0; i < 2; i++)
	//{
	//	DeleteGraph(hakoteki[i]);
	//	DeleteGraph(haneteki[i]);
	//	DeleteGraph(happy[i]);
	//}

	//for (i = 0; i < 4; i++)
	//{
	//	DeleteGraph(kinteki[i]);
	//}


}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
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
	/*int i;
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

	}*/
}

//�G�A�j���[�V��������
void Enemy::AnimetionControl()
{
	////�t���[���J�E���g�����Z����
	//animation_count++;

	////30�t���[���ڂɓ��B������
	//if (animation_count >= 30)
	//{
	//	//count�̃��Z�b�g
	//	animation_count = 0;
	//

	//	//�摜�̐؂�ւ�
	//	if (image == hakoteki[0])
	//	{
	//		image = hakoteki[1];
	//	}
	//	else if (image == hakoteki[1])
	//	{
	//		image = hakoteki[0];
	//	}

	//	if (image == haneteki[0])
	//	{
	//		image = haneteki[1];
	//	}
	//	else if(image == haneteki[1])
	//	{
	//		image = haneteki[0];
	//	}

	//	if (image == happy[0])
	//	{
	//		image = happy[1];
	//	}
	//	else if (image == happy[1])
	//	{
	//		image = happy[0];
	//	}

	//}
}