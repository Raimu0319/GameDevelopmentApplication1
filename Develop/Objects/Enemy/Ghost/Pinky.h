#pragma once
#include "../EnemyBase.h"

class Pinky : public EnemyBase
{
public:

	Pinky();		//�R���X�g���N�^
	~Pinky();		//�f�X�g���N�^

	void Initialize() override;	//����������

	void  AnimationControl(float delta_second) override;		//�A�j���[�V��������

private:
	void PlayerChase(float delta_second) override;		//�ǐՏ���
	void GoTerritory(float delta_second) override;		//�꒣�菈��
};
