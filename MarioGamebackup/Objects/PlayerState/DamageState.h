#pragma once

#include "DamageState.h"
#include "Factory/PlayerStateFactory.h"

class DamageState : public PlayerStateBase
{
private:


public:
	//�R���X�g���N�^	p = �v���C���[���
	DamageState(class Player* p);

	//�f�X�g���N�^
	virtual ~DamageState();

public:
	//����������
	void Initialize();

	//�I������
	void Finalize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw() const;

	//���݂̃X�e�[�g�����擾����
	ePlayerState GetState() const override;
};
