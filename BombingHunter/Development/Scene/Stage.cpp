#include "Stage.h"
#include "DxLib.h"

Stage::Stage() : stage_image(NULL),stage_sound(NULL)
{
	stage_image = NULL;
}

Stage::~Stage()
{

}

//初期化処理
void Stage::Initialize()
{
	//画像の読み込み
	stage_image = LoadGraph("Resource/Images/Stage/Stage.png");
}

//更新処理
void Stage::Update()
{
	
}

//終了時処理
void Stage::Finalize()
{
	DeleteGraph(stage_image);
}

//描画処理
void Stage::Draw() const
{
#ifdef D_PIVOT_CENTER

		DrawRotaGraphF(320, 240, 2.0f/3.0f, 0, stage_image, TRUE, 0);

#endif // D_PIVOT_CENTER

	
	//DrawGraph(0.5, 0.5, stage_image, TRUE);
}