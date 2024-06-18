#pragma once

#include "Enemy.h"

class Bullet : public Enemy
{
private:
	//敵画像
	int bullet[2];
	int animation_count;		//アニメーション時間
	Vector2D direction;			//進行方向
	Vector2D P_location;		//プレイヤーの位置座標
	Vector2D target;			//弾の発射地点

public:
	Bullet();
	virtual ~Bullet();

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;		//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_obfect);

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//敵弾の移動方向取得処理
	void SetDirection(const Vector2D& P_Location) override;

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimetionControl();
};
