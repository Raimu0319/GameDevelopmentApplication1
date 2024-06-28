#pragma once
#include "../../GameObject.h"

class E_ScoreEffect : public GameObject
{
private:
	int animation_count;	//�t���[���J�E���g
	int toumeido;			//�����x�����X�ɕω�������
	int shake;				//�摜����������������

public:
	int image;				//�摜
	int filp_flag;			//���]�t���O

public:
	E_ScoreEffect();
	~E_ScoreEffect();

	void Initialize();			//����������
	void Update();				//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I��������	

	void SetImage(int img, int filp_flag);		//�摜�̎擾����
private:
	void EraseAnim();			//�G�l�~�[�̍폜����
};