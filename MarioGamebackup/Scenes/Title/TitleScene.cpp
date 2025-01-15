#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene() :
	title_image(NULL)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::CreateInstance();
	title_image = rm->GetImages("Resource/Images/title.png")[0];
	//// BGMの読み込み
	//title_image = rm->GetSounds("Resource/Sounds/start-music.mp3");
}

eSceneType TitleScene::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::CreateInstance();

	// インゲームシーンに遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw();

	// UIの描画
	DrawRotaGraph(320, 240, 1.0, 0.0, title_image, TRUE);
	/*DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed game start");
	SetFontSize(16);*/
}

void TitleScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}