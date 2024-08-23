#pragma once
#include "../EnemyBase.h"

class Inky : public EnemyBase
{
public:

	Inky();		//コンストラクタ
	~Inky();		//デストラクタ

	// 移動アニメーションの順番
	const int animation_num[2] = { 6, 7 };

	void Initialize() override;	//初期化処理

	void  AnimationControl(float delta_second) override;		//アニメーション制御

private:
	//void PlayerChase(float delta_second) override;		//追跡処理
};
