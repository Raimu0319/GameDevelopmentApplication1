#pragma once

#include "../GameObject.h"
#include "../CreateClass.h"

class Player : public CreateClass
{
private:
	int animation[2];		//�A�j���[�V�����摜
	int animation_count; //�A�j���[�V��������
	int filp_flag;			//���]�t���O
	
public:
	Vector2D velocity;

public:
	Player();
	~Player();

	virtual void Initialize() override;			//����������
	virtual void Update() override;			    //�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;			//�I��������

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ݒ菈��
	void SetLocation(const Vector2D& location);

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimetionControl();
};