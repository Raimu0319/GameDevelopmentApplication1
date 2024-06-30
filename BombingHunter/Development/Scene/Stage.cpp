#include "Stage.h"
#include "DxLib.h"

Stage::Stage() : stage_image(NULL),stage_sound(NULL)
{
	stage_image = NULL;
}

Stage::~Stage()
{

}

//‰Šú‰»ˆ—
void Stage::Initialize()
{
	//‰æ‘œ‚Ì“Ç‚İ‚İ
	stage_image = LoadGraph("Resource/Images/Stage/Stage.png");
}

//XVˆ—
void Stage::Update()
{
	
}

//I—¹ˆ—
void Stage::Finalize()
{
	DeleteGraph(stage_image);
}

//•`‰æˆ—
void Stage::Draw() const
{
#ifdef D_PIVOT_CENTER

		DrawRotaGraphF(320, 240, 2.0f/3.0f, 0, stage_image, TRUE, 0);

#endif // D_PIVOT_CENTER

	
	//DrawGraph(0.5, 0.5, stage_image, TRUE);
}