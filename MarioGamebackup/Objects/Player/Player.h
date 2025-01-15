#pragma once

#include "../Character.h"

enum ePlayerState : unsigned char
{
	eIDLE,
	eWALK,
	eJUMP,
	eATTACK,
	eDAMAGE,
	eGOAL,
	eDIE,
	eNONE
};

class Player : public Character
{
private:
	class PlayerStateBase* state = nullptr;			//���݂̏��
	ePlayerState next_state = ePlayerState::eNONE;	//���̏��
	ePlayerState now_state = ePlayerState::eIDLE;	//���݂̃X�e�[�g���

	ePlayerState player_stae;				//�v���C���[�̏��
	float star_time;						//���G����
	bool is_power;							//�p���[�A�b�v��Ԃ�
	bool is_star;							//���G���Ԓ���

public:
	Player();
	~Player();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void OnHitCollision(GameObject*) override;		//�R���W����
	//ePlayerState GetPlayerState() const;			//�X�e�[�g�̎擾
	void SetNextState(ePlayerState next_state);		//����State��ݒ�

private:
	void ChengeMode();
	void AnimationControl(float delta_second) override;
};
