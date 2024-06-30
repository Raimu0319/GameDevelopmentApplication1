#include "GameObject.h"
#include "../Scene/Scene.h"
#include "Player/Player.h"
#include "DxLib.h"

//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	Check_active(NULL),
	bomb_stop(0),
	radian(0.0),
	type(NULL),
	image(NULL),
	sound(NULL),
	scene(nullptr)
{

}

//�f�X�g���N�^
GameObject::~GameObject()
{

}

//����������
void GameObject::Initialize()
{

}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{

}

//�I��������
void GameObject::Finalize()
{
	
}

//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
}

//�\������
int GameObject::GetActive()
{
	return this->Check_active;
}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

void GameObject::GetScenepoint(Scene* scene)
{
	this->scene = scene;
}

//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//�G�e�̈ړ������擾����
void GameObject::SetDirection(const Vector2D& P_Location)
{
	
}

//�����蔻��̑傫����n��
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}

//�I�u�W�F�N�g�̃^�C�v��n��
int GameObject::get_type() const
{
	return type;
}
