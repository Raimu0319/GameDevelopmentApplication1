#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/Kinteki.h"
#include "../Objects/Enemy/Hakoteki.h"
#include "../Objects/Enemy/Haneteki.h"
#include "../Objects/Player/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "Dxlib.h"

//�R���X�g���N�^
Scene::Scene() : objects(),sum_score(0),high_score(0),Finalize_count(0)
{
	int i;

	stage_sound = NULL;

	for (i = 0; i < 10; i++)
	{
		number[i] = NULL;
	}

	img_score = NULL;
	img_high_score = NULL;
	timer_img = NULL;
	finish_img = NULL;

	for (i = 0; i < 4; i++)
	{
		result_img[i] = NULL;
	}

	for (i = 0; i < 4; i++)
	{
		result_se[i] = NULL;
	}
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();

	//���U���g�摜�̍폜
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(result_img[i]);
		DeleteSoundMem(result_se[i]);
	}

	//SE�̍폜
	for (int i = 0; i < 4; i++)
	{
		DeleteSoundMem(result_se[i]);
	}
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	player = CreateObject<Player>(Vector2D(320.0f, 60.0f));

	//�����̓ǂݍ���
	stage_sound = LoadSoundMem("Resource/sounds/BGM_arrows.wav");
	finish_se = LoadSoundMem("Resource/sounds/BGM_timeup.wav");

	//�����摜�̓ǂݍ���
	number[0] = LoadGraph("Resource/Images/Score/0.png");
	number[1] = LoadGraph("Resource/Images/Score/1.png");
	number[2] = LoadGraph("Resource/Images/Score/2.png");
	number[3] = LoadGraph("Resource/Images/Score/3.png");
	number[4] = LoadGraph("Resource/Images/Score/4.png");
	number[5] = LoadGraph("Resource/Images/Score/5.png");
	number[6] = LoadGraph("Resource/Images/Score/6.png");
	number[7] = LoadGraph("Resource/Images/Score/7.png");
	number[8] = LoadGraph("Resource/Images/Score/8.png");
	number[9] = LoadGraph("Resource/Images/Score/9.png");

	img_score = LoadGraph("Resource/Images/Score/font-21.png");			//�X�R�A�摜
	img_high_score = LoadGraph("Resource/Images/Score/hs.png");			//�n�C�X�R�A�摜
	timer_img = LoadGraph("Resource/Images/TimeLimit/timer-03.png");	//�^�C�}�[�摜

	finish_img = LoadGraph("Resource/Images/Evaluation/Finish.png");	//�I���摜

	//���U���g�摜�̓ǂݍ���
	result_img[0] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	result_img[1] = LoadGraph("Resource/Images/Evaluation/OK.png");
	result_img[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	result_img[3] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

	//���U���gSE�̓ǂݍ���
	result_se[0] = LoadSoundMem("Resource/sounds/SE_bad.wav");
	result_se[1] = LoadSoundMem("Resource/sounds/SE_ok.wav");
	result_se[2] = LoadSoundMem("Resource/sounds/SE_good.wav");
	result_se[3] = LoadSoundMem("Resource/sounds/SE_perfect.wav");

	//�G���[�`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (number[i] == -1)
		{
			throw("���ԕ\���摜������܂���\n");
		}
	}

	//���ʂ̒����ƃT�E���h�𗬂�
	ChangeVolumeSoundMem(255 * 80 / 100, stage_sound);
	PlaySoundMem(stage_sound, DX_PLAYTYPE_LOOP, TRUE);
	
	sum_score = 0;

	time_set = 60;					//�������Ԃ̐ݒ�

	startTime = GetNowCount();		//�v���O�����J�n����

	time_sec1 = time_set / 10;		//10�̈�
	
	time_sec2 = time_set % 10;		//1�̈�

	baisu = 1;					//�b���J�E���g

	Finalize_count = 0;				//��x�������s

	se_count = 0;			//���U���g�����s���ꂽ���ǂ���
}

//�X�V����
void Scene::Update()
{	
	Time_Anim();		//���ԏ���

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();

		//���e����������Ă��邩�ǂ���
		if (objects[i]->get_type() == BOMB)
		{
			//���e�̐����𐧌�����
			objects[0]->bomb_stop = 1;
		}
	}
	
	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	// �폜�������I�u�W�F�N�g���폜����
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetActive() == FALSE)
		{
			//�폜���ꂽ�I�u�W�F�N�g�����e���ǂ���
			if (objects[i]->get_type() == BOMB)
			{
				//���e�̐����𐧌�����������
				objects[0]->bomb_stop = 0;
			}

			//�I�u�W�F�N�g���X�g�̐擪(begin)����i�Ԗڂ̃I�u�W�F�N�g���폜(erase)����
			objects.erase(objects.begin() + i);		//erase�Ń��X�g����폜����Ə���ɔz����߂Ă����
			i--;									//�z����l�߂�ƍŌ�̕����ɋ󂫂��ł��邩��f�N�������g����
		}
	}

	//�G�̃����_���X�|�[��
	if (time_set >= 0)
	{
		frame_count++;

		if (frame_count >= 120)
		{
			//0�`8�̐����������_���Ŏ擾���A�G�������_���o��������
			int Random_Enemy = GetRand(8);

			if (Random_Enemy == 0)
			{
				CreateObject<Kinteki>(Vector2D(0.0f, LANE_0));
			}
			else if (Random_Enemy == 1)
			{
				CreateObject<Hakoteki>(Vector2D(0.0f, LANE_1))->GetPlayerpoint(player);
			}
			else if (Random_Enemy == 2)
			{
				CreateObject<Haneteki>(Vector2D(0.0f, LANE_2));
			}
			else if (Random_Enemy == 3)
			{
				CreateObject<Haneteki>(Vector2D(0.0f, LANE_3));
			}

			frame_count = 0;
		}

		//�X�y�[�X�L�[����������A���e�𐶐�����
		if (InputControl::GetKeyDown(KEY_INPUT_Z))
		{
			CreateObject<Hakoteki>(Vector2D(0.0f, LANE_1))->GetPlayerpoint(player);
		}
	}
	
}

//�`�揈��
void Scene::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	Score_Draw();		//�X�R�A�̕`��
	Time_Draw();		//���Ԃ̕`��
}

void Scene::Score_Draw() const
{
	
	DrawRotaGraphF(130, 460, 1.0, 0.0, img_score, TRUE);				//�X�R�A�摜
	DrawRotaGraphF(400, 460, 1.0, 0.0, img_high_score, TRUE);			//�n�C�X�R�A�摜


	//�X�R�A�\��
	if (sum_score < 99999)
	{
		int div = sum_score;
		DrawRotaGraphF(250, 460, 1.0, 0.0, number[div % 10], TRUE);				
		div = div / 10;
		DrawRotaGraphF(235, 460, 1.0, 0.0, number[div % 10], TRUE);			
		div = div / 10;
		DrawRotaGraphF(220, 460, 1.0, 0.0, number[div % 10], TRUE);				
		div = div / 10;
		DrawRotaGraphF(205, 460, 1.0, 0.0, number[div % 10], TRUE);		
		div = div / 10;
		DrawRotaGraphF(190, 460, 1.0, 0.0, number[div % 10], TRUE);
	}
	else
	{
		//�X�R�A���J���X�g�����ꍇ
		DrawRotaGraphF(250, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(235, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(220, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(205, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(140, 460, 1.0, 0.0, number[9], TRUE);				
	}	

	//�n�C�X�R�A�\��
	int div_high = high_score;
	DrawRotaGraphF(520, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(505, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(490, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(475, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(460, 460, 1.0, 0.0, number[div_high % 10], TRUE);
}

void Scene::Time_Draw() const
{
	//�^�C�}�[�摜
	DrawRotaGraphF(20, 460, 0.5, 0.0, timer_img, TRUE);
	//�b���\��
	DrawRotaGraphF(45, 460, 1.0, 0.0, number[time_sec1], TRUE);
	DrawRotaGraphF(60, 460, 1.0, 0.0, number[time_sec2], TRUE);
}

//�X�R�A���Z����
void Scene::Score_count(int score)
{
	this->sum_score += score;

	//�X�R�A���O�ȉ��ɂȂ�Ȃ��悤�ɐݒ�
	if (sum_score < 0)
	{
		sum_score = 0;
	}
}

//�n�C�X�R�A����
void Scene::High_score()
{
	//�n�C�X�R�A��茻�݂̃X�R�A�̕����傫�����ǂ���
	if (high_score < sum_score)
	{
		high_score = sum_score;
	}
}

//�c�莞�ԕ\������
void Scene::Time_Anim()
{
	//�v���O�����J�n���Ԃƌ��݂̎��Ԃ��ׂč��������Ăǂꂮ�炢���Ԃ����������v�Z����
	int now_count = GetNowCount() - startTime;

	//1000ms=1sec
	if (now_count >= 1000 * baisu)
	{
		time_set--;

		baisu++;
	}

	time_sec1 = time_set / 10;			//10�̈�

	time_sec2 = time_set % 10;			//1�̈�
}

//�I��������
void Scene::Finalize()
{
	startTime = GetNowCount();		//�v���O�����J�n����

	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̊J��
	objects.clear();

	//�摜�̍폜
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(number[i]);
	}

	DeleteGraph(img_score);
	DeleteGraph(img_high_score);
	DeleteGraph(timer_img);

	DeleteSoundMem(stage_sound);
}

void Scene::Finish()
{

	//�I������������x�������s
	if (Finalize_count == 0)
	{
		Finalize();

		Finalize_count = 1;

		PlaySoundMem(finish_se, DX_PLAYTYPE_BACK, TRUE);
	}

	//Finifh�摜�̕`��
	DrawRotaGraphF(320, 240, 0.5, 0.0, finish_img, TRUE);

	//�����ŃT�E���h�𗬂�

	//�v���O�����J�n���Ԃƌ��݂̎��Ԃ��ׂč��������Ăǂꂮ�炢���Ԃ����������v�Z����
	int now_count = GetNowCount() - startTime;

	if (now_count >= 3000)
	{
		DeleteGraph(finish_img);

		//���U���g����x�������s
			if (sum_score < 1000)		//BAD
			{
				DrawRotaGraphF(320, 240, 0.5, 0.0, result_img[0], TRUE);

				//SE����x�������s
				if (se_count == 0)
				{
					PlaySoundMem(result_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (sum_score >= 1000 && sum_score < 1500)		//OK
			{
				DrawRotaGraphF(320, 240, 0.2, 0.0, result_img[1], TRUE);

				//SE����x�������s
				if (se_count == 0)
				{
					PlaySoundMem(result_se[1], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (sum_score >= 1500 && sum_score < 3000)			//GOOD
			{
				DrawRotaGraphF(320, 240, 0.5, 0.0, result_img[2], TRUE);

				//SE����x�������s
				if (se_count == 0)
				{
					PlaySoundMem(result_se[2], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (sum_score >= 3000)			//PERFECT
			{
				DrawRotaGraphF(320, 240, 0.5, 0.0, result_img[3], TRUE);

				//SE����x�������s
				if (se_count == 0)
				{
					PlaySoundMem(result_se[3], DX_PLAYTYPE_BACK, TRUE);
				}
			}

			se_count = 1;

		if (now_count >= 5000)
		{
			//���X�^�[�g����
			DrawFormatString(200, 300, GetColor(0, 0, 0), "�X�y�[�X�L�[�������ă��X�^�[�g");
			if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
			{
				//�I����SE���~�߂�
				StopSoundMem(finish_se);

				//���݂̃X�R�A���O���荂����
				High_score();
			
				//����������
				Initialize();
			}
		}
	}
	
}
#ifdef D_PIVOT_CENTER
//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻������j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//��̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//��̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�Ahit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{


}
Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
#endif // D_PIVOT_CENTER