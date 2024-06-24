#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/Kinteki.h"
#include "../Objects/Enemy/Hakoteki.h"
#include "../Objects/Enemy/Haneteki.h"
#include "../Objects/Player/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "Dxlib.h"

//コンストラクタ
Scene::Scene() : objects()
{

}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	player = CreateObject<Player>(Vector2D(320.0f, 60.0f));
}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (int i = 0; i < objects.size(); i++)
	{
			objects[i]->Update();
	}
	
	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	// 削除したいオブジェクトを削除する
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetActive() == FALSE)
		{
			//オブジェクトリストの先頭(begin)からi番目のオブジェクトを削除(erase)する
			objects.erase(objects.begin() + i);		//eraseでリストから削除すると勝手に配列をつめてくれる
			i--;									//配列を詰めると最後の部分に空きができるからデクリメントする
		}
	}

	//敵のランダムスポーン
	frame_count++;

	if (frame_count >= 120)
	{	
		Random_Enemy = GetRand(8);

		if (Random_Enemy == 0)
		{
			CreateObject<Kinteki>(Vector2D(0.0f, LANE_0));
		}
		else if (Random_Enemy == 1)
		{
			CreateObject<Hakoteki>(Vector2D(0.0f, LANE_1))->GetPlayerpoint(player);
		}
		else if (Random_Enemy == 2)
		{
			CreateObject<Haneteki>(Vector2D(0.0f, LANE_2));
		}
		else if (Random_Enemy == 3)
		{
			CreateObject<Haneteki>(Vector2D(0.0f, LANE_3));
		}

		frame_count = 0;
	}

	//スペースキーを押したら、爆弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Hakoteki>(Vector2D(0.0f, LANE_1))->GetPlayerpoint(player);
	}
	
}

//void Scene::deleteEnemy()
//{
//	delete Enemy;
//}

//描画処理
void Scene::Draw() const
{
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の開放
	objects.clear();

}

#ifdef D_PIVOT_CENTER
//当たり判定チェック処理（矩形の中心で当たり判定を取る）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//二つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//二つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);

	}
}
#else

//当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{


}
Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
#endif // D_PIVOT_CENTER

