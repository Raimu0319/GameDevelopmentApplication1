#pragma once

#include "../GameObject.h"
#include "../Character.h"

//現在モード
enum eNowMode
{
	NONE,
	WALK,
	SHELL,
	DIE
};

//エネミーのタイプ
enum eEnemyType
{
	KURIBO = 0,
	NOKONOKO,
};

class EnemyBase : public Character
{
protected:
	eNowMode now_mode;					//現在の状態
	eEnemyType enemy_type;				//敵の種類

public:
	EnemyBase();			//コンストラクタ
	virtual ~EnemyBase();		//デストラクタ

	virtual void Initialize() override;								//初期化処理
	void Finalize() override;									//終了時処理
	void Draw(const Vector2D& screen_offset) const override;		//描画処理
	void Update(float delta_second) override;					//更新処理

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	//virtual void OnHitCollision(GameObjectBase* hit_object) override;

protected:

	virtual void  AnimationControl(float delta_second);		//アニメーション制御

private:
	void Movement(float delta_second);			//移動処理
	
};