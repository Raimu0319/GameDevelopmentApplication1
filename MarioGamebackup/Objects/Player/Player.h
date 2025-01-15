#pragma once

#include "../Character.h"

enum ePlayerState : unsigned char
{
	eIDLE,
	eWALK,
	eJUMP,
	eATTACK,
	eDAMAGE,
	eGOAL,
	eDIE,
	eNONE
};

class Player : public Character
{
private:
	class PlayerStateBase* state = nullptr;			//現在の状態
	ePlayerState next_state = ePlayerState::eNONE;	//次の状態
	ePlayerState now_state = ePlayerState::eIDLE;	//現在のステート状態

	ePlayerState player_stae;				//プレイヤーの状態
	float star_time;						//無敵時間
	bool is_power;							//パワーアップ状態か
	bool is_star;							//無敵時間中か

public:
	Player();
	~Player();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void OnHitCollision(GameObject*) override;		//コリジョン
	//ePlayerState GetPlayerState() const;			//ステートの取得
	void SetNextState(ePlayerState next_state);		//次のStateを設定

private:
	void ChengeMode();
	void AnimationControl(float delta_second) override;
};
