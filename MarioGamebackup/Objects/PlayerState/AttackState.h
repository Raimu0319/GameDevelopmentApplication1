#pragma once

#include "AttackState.h"
#include "Factory/PlayerStateFactory.h"

class AttackState : public PlayerStateBase
{
private:


public:
	//�R���X�g���N�^	p = �v���C���[���
	AttackState(class Player* p);

	//�f�X�g���N�^
	virtual ~AttackState();

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
