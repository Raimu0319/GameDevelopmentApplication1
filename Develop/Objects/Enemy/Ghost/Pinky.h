#pragma once
#include "../EnemyBase.h"

class Pinky : public EnemyBase
{
public:

	Pinky();		//コンストラクタ
	~Pinky();		//デストラクタ

	// 移動アニメーションの順番
	const int animation_num[2] = { 2, 3 };

	void Initialize() override;	//初期化処理

	void  AnimationControl(float delta_second) override;		//アニメーション制御

private:
	//void PlayerChase(float delta_second) override;		//追跡処理
};
