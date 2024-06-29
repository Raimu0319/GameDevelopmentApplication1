#pragma once

#include "../../GameObject.h"
#include "../../CreateClass.h"

class Bomb : public CreateClass
{
private:
	int bomb_img;		//���e�摜
	int explosion_SE;		//���e�����T�E���h
	int animation_count;   //�A�j���[�V��������
	int filp_flag;			//���]�t���O
	Vector2D direction;		//�i�s����
	class Player* player;	//�v���C���[�̃|�C���^		
	Vector2D direction_add;				//���e�̈ړ��ʂ������������Ă����ϐ�

public:
	Bomb();
	~Bomb();

	virtual void Initialize() override;			//����������
	virtual void Update() override;			    //�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;			//�I��������

	virtual void OnHitCollision(GameObject* hit_object) override;		//�����蔻��ʒm����
	void GetPlayerpoint(Player* player);								//�v���C���[�̃|�C���^���擾
	void SetDirection(Vector2D P_velocity);												//�ړ����x�̐ݒ�

private:
	void Movement();	//�ړ�����
};