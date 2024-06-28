#include "../../Scene/Scene.h"
#include "Enemy.h"
#include "Hakoteki.h"
#include "Haneteki.h"
#include "Kinteki.h"
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
	//1�`0�̐����������_���Ŏ擾
	int r = GetRand(1);

	//�G�l�~�[�̃X�s�[�h�������_���ɐݒ肷��
	float speed = (GetRand(2) % 2 * 0.5) + 1.0f;

	//r��1�Ȃ獶����E�Ɉړ�	r��0�Ȃ�E���獶�Ɉړ�
	if (r == 1)
	{
		// �E����
		direction = Vector2D(speed, 0.0f);
		this->location.x = 80.0f;
	}
	else
	{
		// ������
		direction = Vector2D(-speed, 0.0f);
		this->location.x = 580.0f;
	}
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

	//������ɓG�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
	
}

//�I��������
void Enemy::Finalize()
{

}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	
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
	//�摜���]�t���O
	flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//��ʉE�[�ɓ��B������A�폜����
	if ((640.0f - box_size.x) < (location.x / 2))
	{
		this->Check_active = FALSE;
	}

	//��ʍ��[�ɓ��B������A�폜����
	if (location.x < (box_size.x / 2))
	{
		this->Check_active = FALSE;
	}

	//��ʏ�ɓ��B������A�폜����
	if (location.y < 0)
	{
		this->Check_active = FALSE;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

void Enemy::RandomSpwan()
{

}

//�G�A�j���[�V��������
void Enemy::AnimetionControl()
{
	
}