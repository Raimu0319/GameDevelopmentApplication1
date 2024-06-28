#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

//�G���o�Ă��鍂��
#define LANE_0	(420.0f)
#define LANE_1	(350.0f)
#define LANE_2	(300.0f)
#define LANE_3	(200.0f)

//�G�̃X�|�[���ꏊ
#define LEFT_WALL	(0.0f)
#define	RIGHT_WALL	(640.0f)
enum result
{
	BAD,
	OK,
	GOOD,
	PERFECT
};

class Scene
{
private:
	std::vector<GameObject*> objects;		//�I�u�W�F�N�g���X�g
	Vector2D location;
private:
	int img_score;					//�X�R�A�摜
	int img_high_score;					//�X�R�A�摜
	int score;						//�X�R�A
	int sum_score;					//���X�R�A
	int high_score;					//�n�C�X�R�A
	int number[10];						//�O�`�X�܂ł̐����摜

	int time_count;			//�b���J�E���g
	int timer_img;			//�^�C�}�[�摜
	int startTime;			//�v���O�������J�n���ꂽ����
	int baisu;
	
	int time_sec1;			//�b���摜�\��
	int time_sec2;			//�b���摜�\��

	int frame_count;				//�t���[���J�E���g
	int Random_Enemy;				//�G�̃����_���o���p�ϐ�
	class Player* player;			//�v���C���[�̃|�C���^

	int finish_img;					//�Q�[���I���摜
	int result_img[4];					//�ŏI���ʉ摜

	int wait_time;					//��莞�ԃX�g�b�v

	int oneplay;					//��x�������s
		
public:
	int time_set;			//�������Ԑݒ�

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();					//�v���O�����I��������

	void Score_count(int score);		//�X�R�A���Z����
	int High_score();					//���݂̃X�R�A���n�C�X�R�A��
	void Score_Draw() const;					//�X�R�A�`�揈��
	
	void Time_Draw() const;				//���ԕ`�揈��
	void Time_Anim();					//���ԕ\������

	void Finish();						//�Q�[���I��������

public:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObfect�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//����������
		new_object->Initialize();

		//scene�̃|�C���^��n��
		new_object->GetScenepoint(this);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};