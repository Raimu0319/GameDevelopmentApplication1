#pragma once
#include "../EnemyBase.h"

class Pinky : public EnemyBase
{
public:

	Pinky();		//�R���X�g���N�^
	~Pinky();		//�f�X�g���N�^

	// �ړ��A�j���[�V�����̏���
	const int animation_num[2] = { 2, 3 };

	void Initialize() override;	//����������

	void  AnimationControl(float delta_second) override;		//�A�j���[�V��������

private:
	//void PlayerChase(float delta_second) override;		//�ǐՏ���
};
