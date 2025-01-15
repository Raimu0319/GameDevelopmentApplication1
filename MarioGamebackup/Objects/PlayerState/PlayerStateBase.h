#pragma once
#include "../Player/Player.h"

//プレイヤー状態管理用のベースクラス
class PlayerStateBase
{
protected:

	class Player* player;					//プレイヤー情報
	int animation_count;					//アニメーションカウント
	std::vector<int> move_animation;		//アニメーション画像


public:
	//コンストラクタ	p = プレイヤー情報
	PlayerStateBase(class Player* p) : player(p),move_animation(NULL)
	{

	}

	//デストラクタ
	virtual ~PlayerStateBase() = default;

public:
	//初期化処理関数
	virtual void Initialize() = 0;

	//終了処理関数
	virtual void Finalize() = 0;

	//更新処理
	virtual void Update(float deleta_second) = 0;

	//描画処理
	virtual void Draw() const = 0;

	//状態の取得
	virtual ePlayerState GetState() const = 0;
};
