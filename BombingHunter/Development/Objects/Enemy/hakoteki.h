#pragma once

#include "Enemy.h"

class Hakoteki : public Enemy
{
private:
	//敵画像
	int hakoteki[2];
	int wait_count;			//弾の発射時間
	int animation_count;		//アニメーション時間
	Vector2D direction;		//進行方向
	class Player* player;			//プレイヤーのポインタ

public:
	Hakoteki();
	virtual ~Hakoteki();

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;		//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_obfect);

	//弾の生成処理
	void BulletCreate();

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//プレイヤーのポインタを取得
	void GetPlayerpoint(Player* player);

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimetionControl();
};


