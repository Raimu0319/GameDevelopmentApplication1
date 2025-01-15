#pragma once

#include "GoalState.h"
#include "Factory/PlayerStateFactory.h"

class GoalState : public PlayerStateBase
{
private:


public:
	//コンストラクタ	p = プレイヤー情報
	GoalState(class Player* p);

	//デストラクタ
	virtual ~GoalState();

public:
	//初期化処理
	void Initialize();

	//終了処理
	void Finalize();

	//更新処理
	void Update();

	//描画処理
	void Draw() const;

	//現在のステート情報を取得する
	ePlayerState GetState() const override;
};
