#include "EnemyEffect.h"
#include "DxLib.h"

EnemyEffect::EnemyEffect() : animation_count(0), filp_flag(0),shake(0)
{

}

EnemyEffect::~EnemyEffect()
{

}

void EnemyEffect::Initialize()
{
	type = EFFECT;		//�I�u�W�F�N�g�^�C�v�̐ݒ�

	Check_active = TRUE;				//�\�����邩���Ȃ���

	toumeido = 255;

	image = NULL;
}

void EnemyEffect::Update()
{
	MoveEffect();
	EraseAnim();
}

void EnemyEffect::Draw() const
{
	//�G��������G�t�F�N�g�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, toumeido);
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void EnemyEffect::Finalize()
{
	image = NULL;
}

void EnemyEffect::SetImage(int img,int filp_flag)
{
	this->image = img;

	this->filp_flag = filp_flag;
}

void EnemyEffect::MoveEffect()
{
	if (shake == 0)
	{
		location.x += 7.0f;

		shake = 1;
	}
	else
	{
		location.x -= 7.0f;

		shake = 0;
	}

	location.y += 0.5f;
}

void EnemyEffect::EraseAnim()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//10�t���[���ڂɓ��B������
	if (animation_count >= 10)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//���X�ɓ����ɂ��Ă���
		toumeido -= 50;
	}

	if (toumeido <= 0)
	{
		Check_active = FALSE;
	}
}