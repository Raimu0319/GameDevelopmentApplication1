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
enum result
{
	BAD,
	OK,
	GOOD,
	PERFECT
};

class Scene
{
private:
	std::vector<GameObject*> objects;		//オブジェクトリスト
	Vector2D location;
private:
	int img_score;					//スコア画像
	int img_high_score;					//スコア画像
	int score;						//スコア
	int sum_score;					//総スコア
	int high_score;					//ハイスコア
	int number[10];						//０～９までの数字画像

	int time_count;			//秒数カウント
	int timer_img;			//タイマー画像
	int startTime;			//プログラムが開始された時間
	int baisu;
	
	int time_sec1;			//秒数画像表示
	int time_sec2;			//秒数画像表示

	int frame_count;				//フレームカウント
	int Random_Enemy;				//敵のランダム出現用変数
	class Player* player;			//プレイヤーのポインタ

	int finish_img;					//ゲーム終了画像
	int result_img[4];					//最終結果画像

	int wait_time;					//一定時間ストップ

	int oneplay;					//一度だけ実行
		
public:
	int time_set;			//制限時間設定

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();					//プログラム終了時処理

	void Score_count(int score);		//スコア加算処理
	int High_score();					//現在のスコアがハイスコアか
	void Score_Draw() const;					//スコア描画処理
	
	void Time_Draw() const;				//時間描画処理
	void Time_Anim();					//時間表示処理

	void Finish();						//ゲーム終了時処理

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

		//sceneのポインタを渡す
		new_object->GetScenepoint(this);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};