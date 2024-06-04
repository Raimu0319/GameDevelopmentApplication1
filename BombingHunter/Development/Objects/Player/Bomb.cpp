#include "Bomb.h"
#include "Player.h"
#include "DxLib.h"

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Bomb/bakuhatu1.png");
	animation[2] = LoadGraph("Resource/Images/Bomb/bakuhatu2.png");
	animation[3] = LoadGraph("Resource/Images/Bomb/bakuhatu3.png");

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
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�I�u�W�F�N�g�̃^�C�v
	type = player;

	//�ړ��̑���
	direction = 2.0f;
}

//�X�V����
void Bomb::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimetionControl();
}

//�`�揈��
void Bomb::Draw() const
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
void Bomb::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->get_type() == enemy)
	{
		//direction = 0.0f;

		location.y += direction.y;

		image = animation[1];
	}
}

//�ړ�����
void Bomb::Movement()
{
	//���e����ʊO�ɓ��B�����Ƃ��̏����@
	if (location.y > 480.0f)
	{
		direction.y = 0.0f;
	}

	//�摜�������G�t�F�N�g�̏ꍇ
	if (image == animation[1] || image == animation[2] ||
		image == animation[3])
	{
		direction.y = 0.0f;
	}

	//���݂̈ʒu���W�ɑ��������Z����
	location.y += direction.y;
}

//�A�j���[�V��������
void Bomb::AnimetionControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[1])
		{
			image = animation[2];
		}
		else if(image == animation[2])
		{
			image = animation[3];
		}
	}
}