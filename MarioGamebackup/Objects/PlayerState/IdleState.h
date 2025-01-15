#pragma once

#include "IdleState.h"
#include "Factory/PlayerStateFactory.h"

class IdleState : public PlayerStateBase
{
private:


public:
	//コンストラクタ	p = プレイヤー情報
	IdleState(class Player* p);

	//デストラクタ
	virtual ~IdleState();

public:
	//初期化処理
	void Initialize();

	//終了処理
	void Finalize();

	//更新処理
	void Update(float delta_second);

	//描画処理
	void Draw() const;

	//現在のステート情報を取得する
	ePlayerState GetState() const override;
};
