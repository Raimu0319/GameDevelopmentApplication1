#include "IdleState.h"

#include "DxLib.h"
#include "../../Utility/InputManager.h"
#include "../Player/Player.h"

//コンストラクタ	p = プレイヤー情報
IdleState::IdleState(class Player* p)
	: PlayerStateBase(p)
{

}

//デストラクタ
IdleState::~IdleState()
{

}

//初期化処理
void IdleState::Initialize()
{
	//速度を０にする
	player->velocity = 0.0f;
}

//終了処理
void IdleState::Finalize()
{

}

//更新処理
void IdleState::Update(float delta_second)
{
	InputManager* input = InputManager::CreateInstance();

	//ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		player->SetNextState(ePlayerState::eJUMP);
	}

	//追加したchord
//移動状態に遷移
	if ((input->GetKey(KEY_INPUT_A) == true) || (input->GetKey(KEY_INPUT_D) == true))
	{
		player->SetNextState(ePlayerState::eWALK);
	}
}

//描画処理
void IdleState::Draw() const
{
	
}

//現在のステート情報を取得する　return = 現在のステート情報
ePlayerState IdleState::GetState() const
{
	return ePlayerState::eIDLE;
}