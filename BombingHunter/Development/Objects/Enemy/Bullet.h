#pragma once

#include "Enemy.h"

class Bullet : public CreateClass
{
private:
	//�G�摜
	int bullet[2];				//�e�L�e�摜
	int hit_SE;					//�e�L�e�q�b�g�T�E���h
	int animation_count;		//�A�j���[�V��������
	Vector2D target;			//�e�̔��˒n�_
	Vector2D direction;			//�i�s����

public:
	Bullet();
	virtual ~Bullet();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_obfect);

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�G�e�̈ړ������擾����
	void SetDirection(const Vector2D& P_Location);

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimetionControl();
};
