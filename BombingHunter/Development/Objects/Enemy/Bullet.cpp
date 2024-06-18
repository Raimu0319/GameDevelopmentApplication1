#include "../../Scene/Scene.h"
#include "Bullet.h"
#include "../Player/Player.h"
#include "DxLib.h"

//�R���X�g���N�^
Bullet::Bullet()
{
	bullet[0] = NULL;
}

//�f�X�g���N�^
Bullet::~Bullet()
{

}

//����������
void Bullet::Initialize()
{

	//�摜�̓ǂݍ���
	bullet[0] = LoadGraph("Resource/Images/Effect/eff1.png");

	//�G���[�`�F�b�N
	if (bullet[0] == -1)
	{
		throw("�e�L�e�̉摜������܂���\n");
	}


	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 40.0f;

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	type = ENEMY_BULLET;

	//�\�����邩���Ȃ���
	Check_active = TRUE;

	//�����摜�̐ݒ�
	image = bullet[0];
}

//�X�V����
void Bullet::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimetionControl();

}

//�`�揈��
void Bullet::Draw() const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bullet::Finalize()
{
		DeleteGraph(bullet[0]);
}

//�����蔻��ʒm����
void Bullet::OnHitCollision(GameObject* hit_object)
{
	//�G���m���G�ꂽ�ꍇ
	if (hit_object->get_type() == PLAYER)
	{
		//�����������ɍs������
		direction = 0.0f;

		Check_active = FALSE;
	}

}

//�ʒu���擾����
Vector2D Bullet::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ菈��
void Bullet::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�G�e�̈ړ������擾����
void Bullet::SetDirection(const Vector2D& P_Location)
{
	Vector2D vec=  P_Location - this->location;
	float r = atan2f(vec.y, vec.x);
	direction = Vector2D((sinf(r)), -(cosf(r)));

}

//�ړ�����
void Bullet::Movement()
{
	__super::Movement();
}

//�G�A�j���[�V��������
void Bullet::AnimetionControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{

		image = bullet[0];
		//count�̃��Z�b�g
		animation_count = 0;

	}
}