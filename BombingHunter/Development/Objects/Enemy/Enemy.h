#pragma once

#include "../GameObject.h"

class Enemy : public GameObject
{
protected:
	int animation_count;			//アニメーション時間
	int filp_flag;			//反転フラグ

private:
	//敵画像
	int hakoteki[2];
	int haneteki[2];
	int happy[2];
	int kinteki[5];

public:
	Enemy();
	virtual ~Enemy();

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
	//アニメーション制御
	void EnemyAnimeControl();
};
