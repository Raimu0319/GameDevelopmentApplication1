#pragma once

#include "Enemy.h"

class Kinteki : public Enemy
{
private:
	int kinteki[5];
	int kinteki_SE;					//キンテキサウンドSE

	int animation_count;		//アニメーション時間
	Vector2D direction;		//進行方向


public:
	Kinteki();
	virtual ~Kinteki();

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

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimetionControl();
};


