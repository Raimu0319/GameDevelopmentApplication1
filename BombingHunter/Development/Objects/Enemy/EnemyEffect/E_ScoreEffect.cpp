#include "E_ScoreEffect.h"
#include "DxLib.h"

E_ScoreEffect::E_ScoreEffect() : animation_count(0), filp_flag(0),image(NULL),toumeido(255)
{
	e_score_img[0] = NULL;
	e_score_img[1] = NULL;
	e_score_img[2] = NULL;
	e_score_img[3] = NULL;
}

E_ScoreEffect::~E_ScoreEffect()
{

}

//����������
void E_ScoreEffect::Initialize()
{
	//�摜�̓ǂݍ���
	e_score_img[0] = LoadGraph("Resource/Images/Evaluation/Score_Hako.png");
	e_score_img[1] = LoadGraph("Resource/Images/Evaluation/Score_Hane.png");
	e_score_img[2] = LoadGraph("Resource/Images/Evaluation/Score_Hapi.png");
	e_score_img[3] = LoadGraph("Resource/Images/Evaluation/Score_Kin.png");

	//�G���[�`�F�b�N
	/*for (int i = 0; i < 4; i++)
	{
		if (e_score_img[i] == -1);
		{
			throw("�G�X�R�A�摜���ǂݍ��݂ł��܂���ł���");
		}
	}*/

	type = EFFECT;		//�I�u�W�F�N�g�^�C�v�̐ݒ�

	Check_active = TRUE;		//�\�����邩���Ȃ���

	toumeido = 255;				//�����x�̐ݒ�i0�����S�����F255���s���S�����j

	image = NULL;				//�摜�̐ݒ�

	Direction.x = 1.0f;			//�ړ��ʂ̐ݒ�
	Direction.y = -1.0f;

	start_location = location;	//�������W
}

//�X�V����
void E_ScoreEffect::Update()
{
	MoveScore();
	EraseAnim();
}

//�`�揈��
void E_ScoreEffect::Draw() const
{
	//�G��������G�t�F�N�g�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, toumeido);
	DrawRotaGraphF(location.x, location.y, 0.1, radian, image, TRUE, filp_flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�I��������
void E_ScoreEffect::Finalize()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(e_score_img[i]);
	}

	image = NULL;
}

void E_ScoreEffect::MoveScore()
{
	//�������W����ǂꂾ����������
	Vector2D mov_loc = start_location - location;
	if (mov_loc.y > 15.0f)
	{
		Direction.x = 0.5f;
		Direction.y = 1.0f;
	}
	
	location += Direction;
}

//Enemy�̃X�R�A�擾����
void E_ScoreEffect::SetScoreImage(int score)
{
	if (score == 200)			//�n�R�e�L�̏ꍇ
	{
		image = e_score_img[0];
	}
	else if (score == 30)		//�n�l�e�L�̏ꍇ
	{
		image = e_score_img[1];
	}
	else if (score == -100)		//�n�[�s�B�̏ꍇ
	{
		image = e_score_img[2];
	}
	else if (score == 1500)		//�L���e�L�̏ꍇ
	{
		image = e_score_img[3];
	}

	this->filp_flag = filp_flag;

	if (image == -1)
	{
		throw("�n�R�e�L�摜������܂���\n");
	}
}

//�A�j���[�V��������
void E_ScoreEffect::EraseAnim()
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

	//�����x��0�ȉ��ɂȂ������I�u�W�F�N�g������
	if (toumeido <= 0)
	{
		Check_active = FALSE;
	}
}