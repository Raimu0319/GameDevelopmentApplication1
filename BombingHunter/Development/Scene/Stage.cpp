#include "Stage.h"
#include "DxLib.h"

Stage::Stage() : stage_image(NULL)
{

}

Stage::~Stage()
{

}

void Stage::Initialize()
{
	stage_image = LoadGraph("Resource/Images/Stage/Stage.png");
}

void Stage::Update()
{
	
}

void Stage::Finalize()
{
	if (stage_image != NULL)
	{
		return;
	}
	else 
	{
		DeleteGraph(stage_image);
	}
}

void Stage::Draw() const
{
#ifdef D_PIVOT_CENTER

		DrawRotaGraphF(320, 240, 2.0f/3.0f, 0, stage_image, TRUE, 0);

#endif // D_PIVOT_CENTER

	
	//DrawGraph(0.5, 0.5, stage_image, TRUE);
}