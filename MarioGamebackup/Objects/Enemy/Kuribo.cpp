#include "Kuribo.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Kuribo::Kuribo()
{

}

Kuribo::~Kuribo()
{

}

void Kuribo::Initialize()
{

	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = (32.0f, 32.0f);

	//�̗͂̐ݒ�
	hit_point = 1;

	//�����摜�̐ݒ�
	image = move_animation[0];
}

void Kuribo::Finalize()
{

}

void Kuribo::Update(float delta_second)
{
	////�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//�ړ��̎��s
	location += velocity * delta_second;

	//330.0f�n�_��n�ʂƉ���
	if (330.0f < location.y)
	{
		location.y = 330.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}

	AnimationControl(delta_second);
}

//void Kuribo::Draw(const Vector2D& screen_offset) const
//{
//	DrawFormatString(10, 120, GetColor(255, 255, 255), "�G�l�~�[���W:%f", this->location.x);
//}

void Kuribo::AnimationControl(float delta_second)
{

}