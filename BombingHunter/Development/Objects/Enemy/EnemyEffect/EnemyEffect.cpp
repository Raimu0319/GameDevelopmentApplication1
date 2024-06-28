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
	Check_active = TRUE;				//�\�����邩���Ȃ���

	toumeido = 255;

	image = NULL;
}

void EnemyEffect::Update()
{
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

	if (image == -1)
	{
		throw("�n�R�e�L�摜������܂���\n");
	}
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

		if (shake == 0)
		{
			location.x += 5.0f;
			
			shake = 1;
		}
		else
		{
			location.x -= 5.0f;

			shake = 0;
		}

		location.y += 2.0f;

	}

	if (toumeido <= 0)
	{
		Check_active = FALSE;
	}
}