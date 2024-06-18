#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/Kinteki.h"
#include "../Objects/Enemy/Hakoteki.h"
#include "../Objects/Enemy/Haneteki.h"
#include "../Objects/Player/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "Dxlib.h"

//�R���X�g���N�^
Scene::Scene() : objects()
{

}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 60.0f));

}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (int i = 0; i < objects.size(); i++)
	{
			objects[i]->Update();
	}
	
	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	// �폜�������I�u�W�F�N�g���폜����
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetActive() == FALSE)
		{
			objects.erase(objects.begin() + i);
			i--;
		}
	}

	// �n�R�e�L����e�����˂��ꂽ���m�F����
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->get_type() == ENEMY_BULLET)
		{
			objects[i]->SetDirection(objects[0]->GetLocation());
		}
	}

	//�G�̃����_���X�|�[��
	frame_count++;

	if (frame_count >= 120)
	{	
		Random_Enemy = GetRand(8);

		if (Random_Enemy == 0)
		{
			CreateObject<Kinteki>(Vector2D(0.0f, LANE_0));
		}
		else if (Random_Enemy == 1)
		{
			CreateObject<Hakoteki>(Vector2D(0.0f, LANE_1));
		}
		else if (Random_Enemy == 2)
		{
			CreateObject<Haneteki>(Vector2D(0.0f, LANE_2));
		}
		else if (Random_Enemy == 3)
		{
			CreateObject<Haneteki>(Vector2D(0.0f, LANE_3));
		}

		frame_count = 0;
	}
	
}

//void Scene::deleteEnemy()
//{
//	delete Enemy;
//}

//�`�揈��
void Scene::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̊J��
	objects.clear();

}

#ifdef D_PIVOT_CENTER
//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻������j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//��̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//��̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�Ahit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);

	}
}
#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{


}
Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
#endif // D_PIVOT_CENTER

