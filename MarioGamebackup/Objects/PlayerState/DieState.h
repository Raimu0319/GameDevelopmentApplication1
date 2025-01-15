#pragma once

#include "DieState.h"
#include "Factory/PlayerStateFactory.h"

class DieState : public PlayerStateBase
{
private:


public:
	//�R���X�g���N�^	p = �v���C���[���
	DieState(class Player* p);

	//�f�X�g���N�^
	virtual ~DieState();

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
