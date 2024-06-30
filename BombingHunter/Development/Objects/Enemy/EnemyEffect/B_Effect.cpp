#include "B_Effect.h"
#include "DxLib.h"

B_Effect::B_Effect() : animation_count(0), filp_flag(0),image(NULL),toumeido(255)
{
		b_eff_img[0] = NULL;
		b_eff_img[1] = NULL;
		b_eff_img[2] = NULL;
}

B_Effect::~B_Effect()
{

}

void B_Effect::Initialize()
{
	//�摜�̓ǂݍ���
	b_eff_img[0] = LoadGraph("Resource/Images/Effect/eff1.png");
	b_eff_img[1] = LoadGraph("Resource/Images/Effect/eff2.png");
	b_eff_img[2] = LoadGraph("Resource/Images/Effect/eff3.png");

	type = EFFECT;		//�I�u�W�F�N�g�^�C�v�̐ݒ�

	Check_active = TRUE;				//�\�����邩���Ȃ���

	image = b_eff_img[0];
}

void B_Effect::Update()
{
	AnimControl();
}

void B_Effect::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, filp_flag);
}

void B_Effect::Finalize()
{
	int i;
	
	//�摜�̊J��
	for (i = 0; i < 3; i++)
	{
		DeleteGraph(b_eff_img[i]);
	}

	image = NULL;
}

void B_Effect::AnimControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//10�t���[���ڂɓ��B������
	if (animation_count >= 20)
	{
		//count�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == b_eff_img[0])
		{
			image = b_eff_img[1];
		}
		else if (image == b_eff_img[1])
		{
			image = b_eff_img[2];
		}
		else if (image == b_eff_img[2])
		{
			Check_active = FALSE;
		}
	}
}