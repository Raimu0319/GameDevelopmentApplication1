#pragma once
#include "../EnemyBase.h"

class Clyde : public EnemyBase
{
public:

	Clyde();		//コンストラクタ
	~Clyde();		//デストラクタ

	void Initialize() override;	//初期化処理

	void  AnimationControl(float delta_second) override;		//アニメーション制御

private:
	//void PlayerChase(float delta_second) override;		//追跡処理
};
