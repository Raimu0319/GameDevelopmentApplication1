#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

//�G���o�Ă��鍂��
#define LANE_0	(420.0f)
#define LANE_1	(350.0f)
#define LANE_2	(300.0f)
#define LANE_3	(200.0f)

//�G�̃X�|�[���ꏊ
#define LEFT_WALL	(0.0f)
#define	RIGHT_WALL	(640.0f)

class Scene
{
private:
	std::vector<GameObject*> objects;		//�I�u�W�F�N�g���X�g
	Vector2D location;
	int frame_count;			//�t���[���J�E���g
	int Random_Enemy;	

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

public:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObfect�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//����������
		new_object->Initialize();

		new_object->Getpoint(this);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};