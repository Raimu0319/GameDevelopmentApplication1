#pragma once

#include "../GameObject.h"

class Enemy : public GameObject
{
protected:
	int animation_count;			//�A�j���[�V��������
	int filp_flag;			//���]�t���O

private:
	//�G�摜
	int hakoteki[2];
	int haneteki[2];
	int happy[2];
	int kinteki[5];

public:
	Enemy();
	virtual ~Enemy();

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
	//�A�j���[�V��������
	void EnemyAnimeControl();
};
