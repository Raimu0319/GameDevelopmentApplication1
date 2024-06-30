#include "GameObject.h"
#include "../Scene/Scene.h"
#include "Player/Player.h"
#include "DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	Check_active(NULL),
	bomb_stop(0),
	radian(0.0),
	type(NULL),
	image(NULL),
	sound(NULL),
	scene(nullptr)
{

}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize()
{

}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{

}

//終了時処理
void GameObject::Finalize()
{
	
}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
}

//表示判定
int GameObject::GetActive()
{
	return this->Check_active;
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

void GameObject::GetScenepoint(Scene* scene)
{
	this->scene = scene;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//敵弾の移動方向取得処理
void GameObject::SetDirection(const Vector2D& P_Location)
{
	
}

//当たり判定の大きさを渡す
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}

//オブジェクトのタイプを渡す
int GameObject::get_type() const
{
	return type;
}
