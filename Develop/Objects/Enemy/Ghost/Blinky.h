#pragma once
#include "../EnemyBase.h"

class Blinky : public EnemyBase
{
public:

	Blinky();		//コンストラクタ
	~Blinky();		//デストラクタ

	// 移動アニメーションの順番
	const int animation_num[2] = { 0, 1 };

	void Initialize() override;	//初期化処理

	void  AnimationControl(float delta_second) override;		//アニメーション制御

private:
	//void PlayerChase(float delta_second) override;		//追跡処理
};
