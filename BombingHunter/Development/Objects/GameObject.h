#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER		//���W�̌��_���摜�̒��S�ɂ���

#define ENEMY (0)			//enemy�������ꍇ
#define PLAYER	(1)			//player�������ꍇ
#define EFFECT	(2)			//effect�������ꍇ
#define ENEMY_BULLET	(3)	//enemy�̒e�������ꍇ
#define BOMB			(4) //���e�������ꍇ

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;				//�ʒu���
	Vector2D box_size;				//�Z�`�̑傫��
	double radian;					//����
	int image;						//�`�悷��摜
	int sound;						//�Đ����鉹��
	int type;						// �I�u�W�F�N�g�^�C�v
	class Scene* scene;				//scene�̃|�C���^
	//class Player* player;			//player�̃|�C���^
	int Check_active;				//�\�����邩���Ȃ���

public:
	int bomb_stop;			//���e�̐�������

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();		//����������
	virtual void Update();			//�X�V����
	virtual void Draw() const;		//�`�揈��
	virtual void Finalize();		//�I��������
		

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_obfect);

	//�I�u�W�F�N�g����ʂɕ\�����邩���Ȃ���(TRUE�Ȃ�\���AFALSE�Ȃ��\��)
	int GetActive();

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�V�[���̃|�C���^���擾
	void GetScenepoint(class Scene* scene);

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�G�e�̈ړ������擾����
	void SetDirection(const Vector2D& P_Location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;

	//�����蔻��̋��
	int get_type() const;

};
