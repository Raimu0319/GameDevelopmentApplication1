#pragma once

#include "Enemy.h"

class Hakoteki : public Enemy
{
private:
	//�G�摜
	int hakoteki[2];
	int wait_count;			//�e�̔��ˎ���
	int animation_count;		//�A�j���[�V��������
	Vector2D direction;		//�i�s����
	class Player* player;			//�v���C���[�̃|�C���^

public:
	Hakoteki();
	virtual ~Hakoteki();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_obfect);

	//�e�̐�������
	void BulletCreate();

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�v���C���[�̃|�C���^���擾
	void GetPlayerpoint(Player* player);

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimetionControl();
};


