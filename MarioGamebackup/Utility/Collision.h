#pragma once

#include "Vector2D.h"
#include <vector>

// オブジェクトタイプ
enum class eObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eGround,
	eBlock,
	eItem,
	eClay_pipe
};

struct HitCheck
{
	//各辺に当たっているかどうかを判定する
	bool H_left;
	bool H_right;
	bool H_top;
	bool H_bottom;
};

// 当たり判定基底クラス
class Collision
{
public:
	//ボックスの当たり判定
	float B_left;		//x座標
	float B_right;		//x + width(x座標と幅を足した数値)
	float B_top;		//y座標
	float B_bottom;		//y + height(y座標と高さを足した数値)
	
	//struct HitCheck
	//{
	//	//各辺に当たっているかどうかを判定する
	//	bool H_left;
	//	bool H_right;
	//	bool H_top;
	//	bool H_bottom;
	//};
	
public:
	bool						is_blocking;		// すり抜けフラグ
	eObjectType					object_type;		// 自身のオブジェクトタイプ
	std::vector<eObjectType>	hit_object_type;	// 適用するオブジェクトタイプ
	Vector2D					location;			// 矩形の座標
	Vector2D					box_size;			// 矩形の座標
	Vector2D					box_location[2];			// 矩形の半径
	Vector2D					point[2];			// 始点と終点（相対座標）
	HitCheck					hitCheck;			//各辺の当たり判定情報

public:
	Collision() :
		is_blocking(false),
		object_type(eObjectType::eNone),
		hit_object_type(),
		location(0.0f, 0.0f),
		box_size(0.0f,0.0f),
		B_left(0.0f),
		B_right(0.0f),
		B_top(0.0f),
		B_bottom(0.0f)/*,
		H_left(false),
		H_right(false),
		H_top(false),
		H_bottom(false)*/
	{
		point[0] = 0.0f;
		point[1] = 0.0f;

		box_location[0] = 0.0f;
		box_location[1] = 0.0f;

	}
	~Collision()
	{
		hit_object_type.clear();
	}

public:
	// 当たり判定有効確認処理
	bool IsCheckHitTarget(eObjectType hit_object) const;

	////オブジェクトが接触しているかどうか
	/*void HitCheckObject(GameObject* a, GameObject* b);*/

};

//矩形状クラス
//class BoxCollision
//{
//public:
//		float B_left;		//x座標
//		float B_right;	//x + width(x座標と幅を足した数値)
//		float B_top;		//y座標
//		float B_bottom;	//y + height(y座標と高さを足した数値)
//
//		bool H_left;
//		bool H_right;
//		bool H_top;
//		bool H_bottom;
//
//public:
//	BoxCollision() :
//		B_left	(0.0f),
//		B_right	(0.0f),
//		B_top	(0.0f),
//		B_bottom(0.0f),
//		H_left	(false),
//		H_right	(false),
//		H_top	(false),
//		H_bottom(false)
//	{
//
//	}
//	~BoxCollision() = default;
//};

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="c1">形状の情報1</param
/// <param name="c2">形状の情報2</param>
/// <returns>当たっているなら、true</returns>
bool IsCheckCollision(Collision& b1, Collision& b2);

//returnでHItCheck型を返して4辺の情報を返す
HitCheck IsHitCheck(Collision& b1, Collision& b2);

//上の処理をvoid型にしてSetCollisionでb1,b2の4辺の情報をいじる
//bool SetCollision()