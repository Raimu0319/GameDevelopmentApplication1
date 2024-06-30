#include "Stage.h"
#include "DxLib.h"

Stage::Stage() : stage_image(NULL),stage_sound(NULL)
{
	stage_image = NULL;
}

Stage::~Stage()
{

}

//����������
void Stage::Initialize()
{
	//�摜�̓ǂݍ���
	stage_image = LoadGraph("Resource/Images/Stage/Stage.png");
}

//�X�V����
void Stage::Update()
{
	
}

//�I��������
void Stage::Finalize()
{
	DeleteGraph(stage_image);
}

//�`�揈��
void Stage::Draw() const
{
#ifdef D_PIVOT_CENTER

		DrawRotaGraphF(320, 240, 2.0f/3.0f, 0, stage_image, TRUE, 0);

#endif // D_PIVOT_CENTER

	
	//DrawGraph(0.5, 0.5, stage_image, TRUE);
}