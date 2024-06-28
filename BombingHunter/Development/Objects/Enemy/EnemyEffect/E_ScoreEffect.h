#pragma once
#include "../../GameObject.h"

class E_ScoreEffect : public GameObject
{
private:
	int animation_count;	//�t���[���J�E���g
	int toumeido;			//�����x�����X�ɕω�������
	int	e_score_img[4];		//�X�R�A�摜
	Vector2D Direction;			//�ړ����x
	Vector2D start_location;	//�������W

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

	void MoveScore();				//�ړ�����
	void SetScoreImage(int score);		//�X�R�A�̎擾����
private:
	void EraseAnim();			//�X�R�A�̍폜����
};
