#pragma once

#include "../GameObject.h"

//現在モード
enum eNowMode
{
	START,
	IZIKE,
	CHASE,
	TERRITORY,
	DEAD
};

//移動方向
enum eDirectionState : unsigned char
{
	E_UP = 0,
	E_RIGHT,
	E_DOWN,
	E_LEFT,
	E_NONE
};

//エネミーのタイプ
enum eEnemyType
{
	BLINKY = 0,
	PINKY,
	CLYDE,
	INKY,
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
	eDirectionState old_direction;			//前回進行方向
	eEnemyType enemy_type;				//敵の種類
	Vector2D e_velocity;				//移動速度
	Vector2D old_location;					// 前回のlocation
	Vector2D territory;					//縄張り座標
	Vector2D loc_diff;					//目標地点との差

	Vector2D const start_point;			//初期地点の座標
	float time_count;					//時間計測
	float animation_time;				//アニメーション時間
	int animation_count;				//アニメーション添字
	int enemycreate_court;				//敵の生成数
	int animation_num[2] = { };		// 移動アニメーションの順番
	float now_time;					//現在時間取得
	float izke_time;					//イジケ時間

	bool search_end;					//探索が終了したかどうか

	//現在パネルからどれほど動いたか
	int move_cost;						//現在位置からどれほど動くか

	//現在座標を添え字に変換
	int ex;		
	int ey;

	//縄張り座標を添え字に変換
	int tx;
	int ty;

	//プレイヤーの座標を添え字に変換
	int px;
	int py;

	//前回添え字保存
	int old_loc;

private:
	int flash_count;					//点滅回数カウント

public:
	EnemyBase();			//コンストラクタ
	virtual ~EnemyBase();		//デストラクタ

	virtual void Initialize() override;								//初期化処理
	void Finalize() override;									//終了時処理
	void Draw(const Vector2D& screen_offset) const override;		//描画処理
	void Update(float delta_second) override;					//更新処理

	void GetPlayerpointer(Player* player);			//プレイヤーのポインタ取得処理

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

protected:
	virtual void PlayerChase(float delta_second);		//プレイヤーを追跡する処理

	virtual void  AnimationControl(float delta_second);		//アニメーション制御

	void RootSearch(int x,int y);			//最短距離探索関数

private:
	void ModeChange(float delta_second);				//敵の状態切り替え
	void Movement(float delta_second);			//移動処理
	void EnemyStart(float delta_second);			//ゲーム開始時処理
	void GoTerritory(float delta_second);		//縄張りに向かう処理
	void EnemyRespawn(float delta_second);		//リスポーン処理
	void EnemyEscape(float delta_second);		//いじけ状態処理
	void EnemyGate();				//トンネルの減速処理	
};