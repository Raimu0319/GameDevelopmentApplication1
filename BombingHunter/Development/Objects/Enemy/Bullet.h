#pragma once

#include "Enemy.h"

class Bullet : public CreateClass
{
private:
	//敵画像
	int bullet;				//テキ弾画像
	int hit_SE;					//テキ弾ヒットサウンド
	Vector2D target;			//弾の発射地点
	Vector2D direction;			//進行方向

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
	void SetDirection(const Vector2D& P_Location);

private:
	//移動処理
	void Movement();
};
