#pragma once
#include "../EnemyBase.h"

class Blinky : public EnemyBase
{
public:

	Blinky();		//�R���X�g���N�^
	~Blinky();		//�f�X�g���N�^

	void Initialize() override;	//����������

	void  AnimationControl(float delta_second) override;		//�A�j���[�V��������

private:
	void PlayerChase(float delta_second) override;		//�ǐՏ���
};
