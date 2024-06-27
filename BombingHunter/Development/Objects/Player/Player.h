#pragma once

#include "../GameObject.h"
#include "../CreateClass.h"

class Player : public CreateClass
{
private:
	int animation[2];		//アニメーション画像
	int animation_count; //アニメーション時間
	int filp_flag;			//反転フラグ
	
public:
	Vector2D velocity;

public:
	Player();
	~Player();

	virtual void Initialize() override;			//初期化処理
	virtual void Update() override;			    //更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;			//終了時処理

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報設定処理
	void SetLocation(const Vector2D& location);

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimetionControl();
};