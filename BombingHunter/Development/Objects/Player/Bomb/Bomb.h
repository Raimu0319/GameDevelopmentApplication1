#pragma once

#include "../../GameObject.h"
#include "../../CreateClass.h"

class Bomb : public CreateClass
{
private:
	int animation;		//�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V��������
	int filp_flag;			//���]�t���O
	Vector2D direction;		//�i�s����
	

public:
	Bomb();
	~Bomb();

	virtual void Initialize() override;			//����������
	virtual void Update() override;			    //�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;			//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimetionControl();
};