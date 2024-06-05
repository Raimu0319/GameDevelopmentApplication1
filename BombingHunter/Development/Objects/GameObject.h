#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER		//座標の原点を画像の中心にする

#define enemy (0)			//enemyだった場合
#define player	(1)			//playerだった場合

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;				//位置情報
	Vector2D box_size;				//短形の大きさ
	double radian;					//向き
	int image;						//描画する画像
	int sound;						//再生する音源
	int type;						// オブジェクトタイプ
	class Scene* scene;					//sceneのポインタ
	

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();		//初期化処理
	virtual void Update();			//更新処理
	virtual void Draw() const;		//描画処理
	virtual void Finalize();		//終了時処理
		

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_obfect);

	//位置情報取得処理
	Vector2D GetLocation() const;

	//シーンのポインタを取得
	virtual void Getpoint(Scene* scene);

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

	//当たり判定の区別
	int get_type() const;
};
