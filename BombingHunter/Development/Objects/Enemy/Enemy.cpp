#include"Enemy.h"
#include"DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() : animation_count(0), filp_flag(FALSE)
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
	//�������p�֐�
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
	scale = 32.0f;

	//�����摜�̐ݒ�
	image = hakoteki[0];
}

//�X�V����
void Enemy::Update()
{
	//�E�ɐi�ݑ�����
	location.x += 1.0f;

	//�E�[�ɍs���ƍ��[�ɖ߂�
	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}
}

//�`�揈��
void Enemy::Draw() const
{
	//�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.6, 0.0, image, TRUE);

	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	//�����蔻��̉���
	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y, GetColor(255,0,0), FALSE);
}

//�I��������
void Enemy::Finalize()
{

}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
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

//�G�A�j���[�V��������
void Enemy::EnemyAnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == hakoteki[0])
		{
			image = hakoteki[1];
		}
		else
		{
			image = hakoteki[0];
		}
	}
}