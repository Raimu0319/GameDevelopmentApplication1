#include "GameObject.h"
#include "../Scenes/SceneBase.h"
#include "DxLib.h"

GameObject::GameObject() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	mobility(eMobilityType::Stationary)
{

}

GameObject::~GameObject()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void GameObject::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void GameObject::Update(float delta_second)
{
	
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void GameObject::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, FALSE, flip_flg);
}

/// <summary>
/// 終了時処理
/// </summary>
void GameObject::Finalize()
{
	move_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void GameObject::OnHitCollision(GameObject* hit_object)
{

}

/// <summary>
/// 所有シーン情報の設定
/// </summary>
/// <param name="scene">所有シーン情報</param>
void GameObject::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

/// <summary>
/// 位置座標取得処理
/// </summary>
/// <returns>位置座標情報</returns>
const Vector2D& GameObject::GetLocation() const
{
	return location;
}

/// <summary>
/// 位置情報変更処理
/// </summary>
/// <param name="location">変更したい位置情報</param>
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

/// <summary>
/// 当たり判定取得処理
/// </summary>
/// <returns>当たり判定情報</returns>
Collision GameObject::GetCollision() const
{
	return collision;
}

//各辺の当たり判定情報
void GameObject::SetCollision(bool t, bool b, bool l, bool r)
{
	this->collision.hitCheck.H_top = t;
	this->collision.hitCheck.H_bottom = b;
	this->collision.hitCheck.H_left = l;
	this->collision.hitCheck.H_right = r;
}

//ボックスサイズ取得処理
Vector2D GameObject::GetBoxsize() const
{
	return this->collision.box_size;
}

/// <summary>
/// Zレイヤー情報取得処理
/// </summary>
/// <returns>Zレイヤー情報</returns>
const int GameObject::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// 可動性情報の取得処理
/// </summary>
/// <returns>可動性情報</returns>
const eMobilityType GameObject::GetMobility() const
{
	return mobility;
}

//画像反転情報
void GameObject::SetFli_flg(int flip_flg)
{
	this->flip_flg = flip_flg;
}

//アニメーション制御
void GameObject::AnimationControl(float delota_second)
{

}