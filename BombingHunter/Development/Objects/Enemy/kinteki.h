#pragma once

#include "Enemy.h"

class Kinteki : public Enemy
{
private:
	int kinteki[5];
	int kinteki_SE;					//�L���e�L�T�E���hSE

	int animation_count;		//�A�j���[�V��������
	Vector2D direction;		//�i�s����


public:
	Kinteki();
	virtual ~Kinteki();

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

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimetionControl();
};


