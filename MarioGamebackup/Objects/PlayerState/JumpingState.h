#pragma once

#include "JumpingState.h"
#include "Factory/PlayerStateFactory.h"

class JumpingState : public PlayerStateBase
{
private:
	//�O�t���[���̍��W���
	Vector2D old_location;
	int hold_count;
	bool jump_flg;

public:
	//�R���X�g���N�^	p = �v���C���[���
	JumpingState(class Player* p);

	//�f�X�g���N�^
	virtual ~JumpingState();

public:
	//����������
	void Initialize();

	//�I������
	void Finalize();

	//�X�V����
	void Update(float delta_second);

	//�`�揈��
	void Draw() const;

	//���݂̃X�e�[�g�����擾����
	ePlayerState GetState() const override;
};
