#pragma once

#include "Enemy.h"

class Haneteki : public Enemy
{
private:
	int haneteki[2];
	int happy[2];

	int haneteki_SE;				//ハネテキ撃破SE
	int hapy_SE;					//ハーピィ撃破SE

public:
	Haneteki();
	virtual ~Haneteki();

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;		//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_obfect);

	//ハネテキかハーピィか
	void RandomSpwan();

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimetionControl();
};


