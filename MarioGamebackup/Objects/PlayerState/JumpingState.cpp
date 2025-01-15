#include "JumpingState.h"

#include "DxLib.h"
#include "../../Utility/InputManager.h"
#include "../Player/Player.h"

//�R���X�g���N�^	p = �v���C���[���
JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p)
	, old_location(Vector2D(0.0f))
	, hold_count(0)
	, jump_flg(true)
{

}

//�f�X�g���N�^
JumpingState::~JumpingState()
{

}

//����������
void JumpingState::Initialize()
{
	this->player->velocity.y -= 700.0f;	//�W�����v��
	old_location = 0.0f;
	hold_count = 0;
	jump_flg = true;
}

//�I������
void JumpingState::Finalize()
{

}

//�X�V����
void JumpingState::Update(float delta_second)
{
	InputManager* input = InputManager::CreateInstance();

	if (jump_flg == true)
	{

 		if (input->GetKey(KEY_INPUT_SPACE) == true)
		{
 			hold_count++;
		}

		if (hold_count == 100)
		{
			this->player->velocity.y -= 400.0f;
		}

   		if (input->GetKeyUp(KEY_INPUT_SPACE))
		{
			jump_flg = false;
		}

	}

	//�ړ���ԂɑJ��
	if (input->GetKey(KEY_INPUT_A) == true)
	{
		player->velocity.x -= 0.5f;
	}

	if (input->GetKey(KEY_INPUT_D) == true)
	{
		player->velocity.x += 0.5f;
	}

	//�n�ʂɐG�ꂽ��
	if (old_location.y == player->GetLocation().y)
	{
		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::eIDLE);
	}

	//�O����W�̍X�V
	old_location = player->GetLocation();
}

//�`�揈��
void JumpingState::Draw() const
{

}

//���݂̃X�e�[�g�����擾����@return = ���݂̃X�e�[�g���
ePlayerState JumpingState::GetState() const
{
	return ePlayerState::eJUMP;
}