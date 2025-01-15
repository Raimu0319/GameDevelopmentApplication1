#pragma once

#include "../Utility/Vector2D.h"
#include <vector>
#include <string>

#include "../Utility/Collision.h"

#define D_OBJECT_SIZE	(24.0f)			// 壁のサイズ

#define D_MASS				(8.0f)	//質量（kg)
#define D_GRAVITY	(9.807f)	//重力加速度(m/ss)
#define D_STATIC_FRICTION	(5.0f)	//静止摩擦係数
#define D_DYNAMIC_FRICTION	(0.3f)	//動摩擦係数

/// <summary>
/// 可動性の種類
/// </summary>
enum eMobilityType
{
	Stationary,		// 固定
	Movable,		// 可動
};

// ゲームオブジェクト基底クラス
class GameObject
{
protected:
	class SceneBase* owner_scene;	// 所有するシーン情報
	std::vector<int> move_animation;		//アニメーション画像
	int animation_count;					//アニメーションカウント
	float animation_time;					// アニメーション時間

	Vector2D			location;	// 位置座標
	Collision			collision;		//矩形の大きさ
	int					image;			// 画像情報
	int					z_layer;		// レイヤー情報
	eMobilityType		mobility;		// 可動性
	float				g_velocity;		//重力速度
	int					flip_flg;		//画像の反転フラグ


public:
	GameObject();
	virtual ~GameObject();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset">オフセット値</param>
	virtual void Draw(const Vector2D& screen_offset) const;
	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize();

public:
	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object);

public:
	/// <summary>
	/// 所有シーン情報の設定
	/// </summary>
	/// <param name="scene">所有シーン情報</param>
	void SetOwnerScene(class SceneBase* scene);

	/// <summary>
	/// 位置座標取得処理
	/// </summary>
	/// <returns>位置座標情報</returns>
	const Vector2D& GetLocation() const;

	/// <summary>
	/// 位置情報変更処理
	/// </summary>
	/// <param name="location">変更したい位置情報</param>
	void SetLocation(const Vector2D& location);

	/// <summary>
	/// 当たり判定取得処理
	/// </summary>
	/// <returns>当たり判定の大きさを取得</returns>
	Collision GetCollision() const;

	//各辺の当たり判定情報
	void SetCollision(bool t, bool b, bool l, bool r);

	//コリジョンサイズ取得処理
	Vector2D GetBoxsize() const;

	/// <summary>
	/// Ｚレイヤー情報取得処理
	/// </summary>
	/// <returns>Ｚレイヤー情報</returns>
	const int GetZLayer() const;

	/// <summary>
	/// 可動性情報の取得処理
	/// </summary>
	/// <returns>可動性情報</returns>
	const eMobilityType GetMobility() const;

	///	反転フラグの切り替え
	///	TRUEかFALSEの数値を返す
	void SetFli_flg(int flip_flg);

	//アニメーション制御
	virtual void AnimationControl(float delta_scond);
};
