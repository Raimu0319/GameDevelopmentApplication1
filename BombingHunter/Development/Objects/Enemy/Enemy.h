#pragma once

#include "../GameObject.h"
#include "../CreateClass.h"

class Enemy : public CreateClass
{
private:
	//�G�摜
	int hakoteki[2];
	int haneteki[2];
	int happy[2];
	int kinteki[5];

	int animation_count;		//�A�j���[�V��������
	Vector2D direction;		//�i�s����

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I��������
	void RandomSpwan();				//�G�������_���o��������

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
