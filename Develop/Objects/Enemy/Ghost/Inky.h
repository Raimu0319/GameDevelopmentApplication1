#pragma once
#include "../EnemyBase.h"

class Inky : public EnemyBase
{
public:

	Inky();		//�R���X�g���N�^
	~Inky();		//�f�X�g���N�^

	// �ړ��A�j���[�V�����̏���
	const int animation_num[2] = { 6, 7 };

	void Initialize() override;	//����������

	void  AnimationControl(float delta_second) override;		//�A�j���[�V��������

private:
	//void PlayerChase(float delta_second) override;		//�ǐՏ���
};
