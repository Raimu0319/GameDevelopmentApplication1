#pragma once

#include "Enemy.h"

class Haneteki : public Enemy
{
private:
	int haneteki[2];
	int happy[2];

public:
	Haneteki();
	virtual ~Haneteki();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_obfect);

	//�n�l�e�L���n�[�s�B��
	void RandomSpwan();

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimetionControl();
};


