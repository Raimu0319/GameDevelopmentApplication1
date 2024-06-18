#include "Bomb.h"
#include "BombEffect.h"
#include "../../Scene/Scene.h"
#include "DxLib.h"

//�R���X�g���N�^
BombEffect::BombEffect() : animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
}

//�f�X�g���N�^
BombEffect::~BombEffect()
{

}

//����������
void BombEffect::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/bakuhatu1.png");
	animation[1] = LoadGraph("Resource/Images/Bomb/bakuhatu2.png");
	animation[2] = LoadGraph("Resource/Images/Bomb/bakuhatu3.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 3; i++)
	{
		if (animation[i] == -1)
		{
			throw("���e�̉摜������܂���\n");
		}
	}

	//�����̐ݒ�
	radian = 0.0;

	//�����蔻��̑傫���ݒ�
	box_size = 0.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�I�u�W�F�N�g�̃^�C�v
	type = EFFECT;

	//�\�����邩���Ȃ���
	Check_active = TRUE;

}

//�X�V����
void BombEffect::Update()
{
	////�ړ�����
	//Movement();
	//�A�j���[�V��������
	AnimetionControl();
}

//�`�揈��
void BombEffect::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, filp_flag);

	//�f�o�b�N�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);

#endif
}

//�I��������
void BombEffect::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
}

//�����蔻��ʒm����
void BombEffect::OnHitCollision(GameObject* hit_object)
{
	/*if (hit_object->get_type() == FALSE)
	{

	}*/
}

//�ړ�����
void BombEffect::Movement()
{
	
}

//�A�j���[�V��������
void BombEffect::AnimetionControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if (image == animation[1])
		{
			image = animation[2];

			Check_active = FALSE;
		}
	}
}