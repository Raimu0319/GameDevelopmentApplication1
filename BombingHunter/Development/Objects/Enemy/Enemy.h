#pragma once

#include "../CreateClass.h"

class Enemy : public CreateClass
{
protected:
	int animation_count;	//�A�j���[�V��������
	Vector2D direction;		//�i�s����
	int score;				//�G�̃X�R�A
	
public:
	int flip_flag;			//���]�t���O

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

protected:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimetionControl();
};

