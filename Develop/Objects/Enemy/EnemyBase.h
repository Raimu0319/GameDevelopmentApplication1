#pragma once

#include "../GameObject.h"

enum eNowMode
{
	START,
	IZIKE,
	CHASE,
	TERRITORY,
	DEAD
};

enum eDirectionState
{
	E_UP = 0,
	E_RIGHT,
	E_DOWN,
	E_LEFT
};

class EnemyBase : public GameObject
{
protected:
	class Player* player;				//プレイヤーのポインタ
	eNowMode now_mode;					//現在の状態
	std::vector<int>move_animation;		//ゴースト画像
	std::vector<int>eye_animation;		//目の画像
	int eye_image;						//目の画像
	eDirectionState direction;			//進行方向
	Vector2D e_velocity;				//移動速度
	Vector2D territory;					//縄張り座標
	Vector2D const start_point;			//初期地点の座標
	float time_count;					//時間計測
	float animation_time;				//アニメーション時間
	int animation_count;				//アニメーション添字
	int enemycreate_court;				//敵の生成数
	int animation_num[2] = { };	// 移動アニメーションの順番

private:
	int flash_count;					//点滅回数カウント

public:
	EnemyBase();			//コンストラクタ
	virtual ~EnemyBase();		//デストラクタ

	virtual void Initialize();								//初期化処理
	void Finalize() override;									//終了時処理
	void Draw(const Vector2D& screen_offset) const override;		//描画処理
	void Update(float delta_second) override;					//更新処理

	void GetPlayerpointer(Player* player);			//プレイヤーのポインタ取得処理

	void EnemyCreate(int enemycreate_court);				//敵の生成処理

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

protected:
	virtual void PlayerChase(float delta_second);		//プレイヤーを追跡する処理

	virtual void  AnimationControl(float delta_second);		//アニメーション制御
private:
	void ModeChange();				//敵の状態切り替え
	void Movement(float delta_second);			//移動処理
	void EnemyStart(float delta_second);			//ゲーム開始時処理
	void GoTerritory(float delta_second);		//縄張りに向かう処理
	void EnemyRespawn(float delta_second);		//リスポーン処理
	void EnemyEscape(float delta_second);		//いじけ状態処理
	void EnemyGate();				//トンネルの減速処理

	

	
};