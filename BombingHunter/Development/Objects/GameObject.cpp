#include "GameObject.h"
#include "../Scene/Scene.h"
#include "DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	radian(0.0),
	type(NULL),
	image(NULL),
	sound(NULL)
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
	//当たり判定の可視化
#ifdef D_PIVOT_CENTER
	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif // D_VPIVOT_CENTER

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

void GameObject::Getpoint(Scene* scene)
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