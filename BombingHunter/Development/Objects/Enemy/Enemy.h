#pragma once

#include "../CreateClass.h"

class Enemy : public CreateClass
{
protected:
	int animation_count;	//アニメーション時間
	Vector2D direction;		//進行方向
	int Random_Wall;		//敵のスポーン場所（右から出るか左から出るか）
	int score;				//敵のスコア

public:

	int spawn;	//出現位置

	Enemy();
	virtual ~Enemy();

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;		//終了時処理

	void RandomSpwan();				//敵をランダム出現させる

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_obfect);

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

protected:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimetionControl();
};

