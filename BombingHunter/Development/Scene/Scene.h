#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

//敵が出てくる高さ
#define LANE_0	(420.0f)
#define LANE_1	(350.0f)
#define LANE_2	(300.0f)
#define LANE_3	(200.0f)

//敵のスポーン場所
#define LEFT_WALL	(0.0f)
#define	RIGHT_WALL	(640.0f)

class Scene
{
private:
	std::vector<GameObject*> objects;		//オブジェクトリスト
	Vector2D location;
	int frame_count;			//フレームカウント
	int Random_Enemy;	

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

public:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObfectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//位置情報の設定
		new_object->SetLocation(location);

		//初期化処理
		new_object->Initialize();

		new_object->Getpoint(this);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};