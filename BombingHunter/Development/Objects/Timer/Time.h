#pragma once

class Time
{
private:
	//�b���J�E���g
	int time_count;
	//�^�C���摜
	int time[10];
	//�^�C�}�[�摜
	int Timer_img;

	//���Ԑݒ�
	int Time_set;
	
	//�b���摜�\��
	int Time_sec1;
	int Time_sec2;

public:

	//�R���X�g���N�^
	Time();
	~Time();

	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw() const;

	//�I������
	void Finalize();

public:
	//���ԕ\������
	void Time_Anim();

};