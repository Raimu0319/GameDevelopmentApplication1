#include "JumpingState.h"

#include "DxLib.h"
#include "../../Utility/InputManager.h"
#include "../Player/Player.h"

//コンストラクタ	p = プレイヤー情報
JumpingState::JumpingState(class Player* p)
	: PlayerStateBase(p)
	, old_location(Vector2D(0.0f))
	, hold_count(0)
	, jump_flg(true)
{

}

//デストラクタ
JumpingState::~JumpingState()
{

}

//初期化処理
void JumpingState::Initialize()
{
	this->player->velocity.y -= 700.0f;	//ジャンプ力
	old_location = 0.0f;
	hold_count = 0;
	jump_flg = true;
}

//終了処理
void JumpingState::Finalize()
{

}

//更新処理
void JumpingState::Update(float delta_second)
{
	InputManager* input = InputManager::CreateInstance();

	if (jump_flg == true)
	{

 		if (input->GetKey(KEY_INPUT_SPACE) == true)
		{
 			hold_count++;
		}

		if (hold_count == 100)
		{
			this->player->velocity.y -= 400.0f;
		}

   		if (input->GetKeyUp(KEY_INPUT_SPACE))
		{
			jump_flg = false;
		}

	}

	//移動状態に遷移
	if (input->GetKey(KEY_INPUT_A) == true)
	{
		player->velocity.x -= 0.5f;
	}

	if (input->GetKey(KEY_INPUT_D) == true)
	{
		player->velocity.x += 0.5f;
	}

	//地面に触れたら
	if (old_location.y == player->GetLocation().y)
	{
		//停止状態に遷移
		player->SetNextState(ePlayerState::eIDLE);
	}

	//前回座標の更新
	old_location = player->GetLocation();
}

//描画処理
void JumpingState::Draw() const
{

}

//現在のステート情報を取得する　return = 現在のステート情報
ePlayerState JumpingState::GetState() const
{
	return ePlayerState::eJUMP;
}