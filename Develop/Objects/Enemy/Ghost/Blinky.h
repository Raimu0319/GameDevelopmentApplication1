#pragma once
#include "../EnemyBase.h"

class Blinky : public EnemyBase
{
public:

	Blinky();		//�R���X�g���N�^
	~Blinky();		//�f�X�g���N�^

	// �ړ��A�j���[�V�����̏���
	const int animation_num[2] = { 0, 1 };

	void Initialize() override;	//����������

	void  AnimationControl(float delta_second) override;		//�A�j���[�V��������

private:
	//void PlayerChase(float delta_second) override;		//�ǐՏ���
};
