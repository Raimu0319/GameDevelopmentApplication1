#pragma once
#include "../EnemyBase.h"

class Clyde : public EnemyBase
{
public:

	Clyde();		//�R���X�g���N�^
	~Clyde();		//�f�X�g���N�^

	void Initialize() override;	//����������

	void  AnimationControl(float delta_second) override;		//�A�j���[�V��������

private:
	//void PlayerChase(float delta_second) override;		//�ǐՏ���
};
