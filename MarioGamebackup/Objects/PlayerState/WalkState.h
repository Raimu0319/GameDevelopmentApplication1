#pragma once

#include "Factory/PlayerStateFactory.h"

class WalkState : public PlayerStateBase
{
private:
	//プレイヤーの移動量
	Vector2D direction;

	//ダッシュ中かどうか
	bool player_dash;

	//入力情報
	//class InputControl* input;

public:
	//コンストラクタ	p = プレイヤー情報
	WalkState(class Player* p);

	//デストラクタ
	virtual ~WalkState();

public:
	//初期化処理
	void Initialize();

	//終了処理
	void Finalize();

	//更新処理
	void Update(float delta_second);

	//描画処理
	void Draw() const;

	//アニメーション制御
	void AnimationControl(float delta_second);

	//現在のステート情報を取得する
	ePlayerState GetState() const override;
};
