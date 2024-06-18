#include "../../Scene/Scene.h"
#include "Hakoteki.h"
#include "Bullet.h"
#include "DxLib.h"

//�R���X�g���N�^
Hakoteki::Hakoteki()
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
	
	//�����摜�̐ݒ�
	image = hakoteki[0];
}

//�X�V����
void Hakoteki::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimetionControl();

	//�e�̐���
	BulletCreate();

}

//�`�揈��
void Hakoteki::Draw() const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
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
	if (hit_object->get_type() == PLAYER)
	{
		//�����������ɍs������
		direction = 0.0f;

		Check_active = FALSE;
	}

}

void Hakoteki::BulletCreate()
{
	wait_count++;

	//�e�̐�������
	if (wait_count >= 120)
	{
		int r;

		r = GetRand(5);

		if (r <= 2)
		{
			//�e�̐���
			CreateObject<Bullet>(Vector2D(this->location.x, this->location.y));
		}

		wait_count = 0;
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
	__super::Movement();
}

void Hakoteki::GetPlayerpoint(Player* player)
{
	this->player = player;
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