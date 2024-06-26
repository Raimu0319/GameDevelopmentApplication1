#include "Bomb.h"
#include "../../Scene/Scene.h"
#include "BombEffect.h"
#include "../Player.h"
#include "DxLib.h"
#include <math.h>

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0), filp_flag(FALSE)
{
	animation = NULL;
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	animation = LoadGraph("Resource/Images/Bomb/Bomb.png");
	
	//�G���[�`�F�b�N
	if (animation == -1)
	{
		throw("���e�̉摜������܂���\n");
	}
	
	//�����̐ݒ�
	radian = DX_PI / 2.0;

	//�����蔻��̑傫���ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation;

	//�I�u�W�F�N�g�̃^�C�v
	type = BOMB;

	//�\�����邩���Ȃ���
	Check_active = TRUE;

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
	DeleteGraph(animation);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->get_type() == ENEMY)
	{
		//direction = 0.0f;

		location.y += direction.y;

		box_size = 0.0;

		Check_active = FALSE;

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
		
	}
}

//�ړ�����
void Bomb::Movement()
{
	//���e����ʊO�ɓ��B�����Ƃ��̏����@
	if (location.y > 380.0f)
	{
		direction.y = 0.0f;

		Check_active = FALSE;

		CreateObject<BombEffect>(Vector2D(this->location.x, this->location.y));
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
		
	}
}