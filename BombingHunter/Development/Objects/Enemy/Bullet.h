#pragma once

#include "Enemy.h"

class Bullet : public Enemy
{
private:
	//�G�摜
	int bullet[2];
	int animation_count;		//�A�j���[�V��������
	Vector2D target;			//�e�̔��˒n�_

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
