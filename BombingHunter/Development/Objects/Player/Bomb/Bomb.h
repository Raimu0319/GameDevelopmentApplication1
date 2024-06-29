#pragma once

#include "../../GameObject.h"
#include "../../CreateClass.h"

class Bomb : public CreateClass
{
private:
	int bomb_img;		//爆弾画像
	int explosion_SE;		//爆弾爆発サウンド
	int animation_count;   //アニメーション時間
	int filp_flag;			//反転フラグ
	Vector2D direction;		//進行方向
	class Player* player;	//プレイヤーのポインタ		
	Vector2D direction_add;				//爆弾の移動量を少しずつ足していく変数

public:
	Bomb();
	~Bomb();

	virtual void Initialize() override;			//初期化処理
	virtual void Update() override;			    //更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;			//終了時処理

	virtual void OnHitCollision(GameObject* hit_object) override;		//当たり判定通知処理
	void GetPlayerpoint(Player* player);								//プレイヤーのポインタを取得
	void SetDirection(Vector2D P_velocity);												//移動速度の設定

private:
	void Movement();	//移動処理
};