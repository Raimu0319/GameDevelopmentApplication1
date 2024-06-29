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
Scene::Scene() : objects(),sum_score(0),high_score(0),Finalize_count(0)
{
	int i;

	stage_sound = NULL;

	for (i = 0; i < 10; i++)
	{
		number[i] = NULL;
	}

	img_score = NULL;
	img_high_score = NULL;
	timer_img = NULL;
	finish_img = NULL;

	for (i = 0; i < 4; i++)
	{
		result_img[i] = NULL;
	}

	for (i = 0; i < 4; i++)
	{
		result_se[i] = NULL;
	}
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();

	//リザルト画像の削除
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(result_img[i]);
		DeleteSoundMem(result_se[i]);
	}

	//SEの削除
	for (int i = 0; i < 4; i++)
	{
		DeleteSoundMem(result_se[i]);
	}
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	player = CreateObject<Player>(Vector2D(320.0f, 60.0f));

	//音源の読み込み
	stage_sound = LoadSoundMem("Resource/sounds/BGM_arrows.wav");
	finish_se = LoadSoundMem("Resource/sounds/BGM_timeup.wav");

	//初期画像の読み込み
	number[0] = LoadGraph("Resource/Images/Score/0.png");
	number[1] = LoadGraph("Resource/Images/Score/1.png");
	number[2] = LoadGraph("Resource/Images/Score/2.png");
	number[3] = LoadGraph("Resource/Images/Score/3.png");
	number[4] = LoadGraph("Resource/Images/Score/4.png");
	number[5] = LoadGraph("Resource/Images/Score/5.png");
	number[6] = LoadGraph("Resource/Images/Score/6.png");
	number[7] = LoadGraph("Resource/Images/Score/7.png");
	number[8] = LoadGraph("Resource/Images/Score/8.png");
	number[9] = LoadGraph("Resource/Images/Score/9.png");

	img_score = LoadGraph("Resource/Images/Score/font-21.png");			//スコア画像
	img_high_score = LoadGraph("Resource/Images/Score/hs.png");			//ハイスコア画像
	timer_img = LoadGraph("Resource/Images/TimeLimit/timer-03.png");	//タイマー画像

	finish_img = LoadGraph("Resource/Images/Evaluation/Finish.png");	//終了画像

	//リザルト画像の読み込み
	result_img[0] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	result_img[1] = LoadGraph("Resource/Images/Evaluation/OK.png");
	result_img[2] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	result_img[3] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

	//リザルトSEの読み込み
	result_se[0] = LoadSoundMem("Resource/sounds/SE_bad.wav");
	result_se[1] = LoadSoundMem("Resource/sounds/SE_ok.wav");
	result_se[2] = LoadSoundMem("Resource/sounds/SE_good.wav");
	result_se[3] = LoadSoundMem("Resource/sounds/SE_perfect.wav");

	//エラーチェック
	for (int i = 0; i < 10; i++)
	{
		if (number[i] == -1)
		{
			throw("時間表示画像がありません\n");
		}
	}

	//音量の調整とサウンドを流す
	ChangeVolumeSoundMem(255 * 80 / 100, stage_sound);
	PlaySoundMem(stage_sound, DX_PLAYTYPE_LOOP, TRUE);
	
	sum_score = 0;

	time_set = 60;					//初期時間の設定

	startTime = GetNowCount();		//プログラム開始時間

	time_sec1 = time_set / 10;		//10の位
	
	time_sec2 = time_set % 10;		//1の位

	baisu = 1;					//秒数カウント

	Finalize_count = 0;				//一度だけ実行

	se_count = 0;			//リザルトが実行されたかどうか
}

//更新処理
void Scene::Update()
{	
	Time_Anim();		//時間処理

	//シーンに存在するオブジェクトの更新処理
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();

		//爆弾が生成されているかどうか
		if (objects[i]->get_type() == BOMB)
		{
			//爆弾の生成を制限する
			objects[0]->bomb_stop = 1;
		}
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
			//削除されたオブジェクトが爆弾かどうか
			if (objects[i]->get_type() == BOMB)
			{
				//爆弾の生成を制限を解除する
				objects[0]->bomb_stop = 0;
			}

			//オブジェクトリストの先頭(begin)からi番目のオブジェクトを削除(erase)する
			objects.erase(objects.begin() + i);		//eraseでリストから削除すると勝手に配列をつめてくれる
			i--;									//配列を詰めると最後の部分に空きができるからデクリメントする
		}
	}

	//敵のランダムスポーン
	if (time_set >= 0)
	{
		frame_count++;

		if (frame_count >= 120)
		{
			//0～8の数字をランダムで取得し、敵をランダム出現させる
			int Random_Enemy = GetRand(8);

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
	
}

//描画処理
void Scene::Draw() const
{
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	Score_Draw();		//スコアの描画
	Time_Draw();		//時間の描画
}

void Scene::Score_Draw() const
{
	
	DrawRotaGraphF(130, 460, 1.0, 0.0, img_score, TRUE);				//スコア画像
	DrawRotaGraphF(400, 460, 1.0, 0.0, img_high_score, TRUE);			//ハイスコア画像


	//スコア表示
	if (sum_score < 99999)
	{
		int div = sum_score;
		DrawRotaGraphF(250, 460, 1.0, 0.0, number[div % 10], TRUE);				
		div = div / 10;
		DrawRotaGraphF(235, 460, 1.0, 0.0, number[div % 10], TRUE);			
		div = div / 10;
		DrawRotaGraphF(220, 460, 1.0, 0.0, number[div % 10], TRUE);				
		div = div / 10;
		DrawRotaGraphF(205, 460, 1.0, 0.0, number[div % 10], TRUE);		
		div = div / 10;
		DrawRotaGraphF(190, 460, 1.0, 0.0, number[div % 10], TRUE);
	}
	else
	{
		//スコアがカンストした場合
		DrawRotaGraphF(250, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(235, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(220, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(205, 460, 1.0, 0.0, number[9], TRUE);				
		DrawRotaGraphF(140, 460, 1.0, 0.0, number[9], TRUE);				
	}	

	//ハイスコア表示
	int div_high = high_score;
	DrawRotaGraphF(520, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(505, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(490, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(475, 460, 1.0, 0.0, number[div_high % 10], TRUE);
	div_high = div_high / 10;
	DrawRotaGraphF(460, 460, 1.0, 0.0, number[div_high % 10], TRUE);
}

void Scene::Time_Draw() const
{
	//タイマー画像
	DrawRotaGraphF(20, 460, 0.5, 0.0, timer_img, TRUE);
	//秒数表示
	DrawRotaGraphF(45, 460, 1.0, 0.0, number[time_sec1], TRUE);
	DrawRotaGraphF(60, 460, 1.0, 0.0, number[time_sec2], TRUE);
}

//スコア加算処理
void Scene::Score_count(int score)
{
	this->sum_score += score;

	//スコアが０以下にならないように設定
	if (sum_score < 0)
	{
		sum_score = 0;
	}
}

//ハイスコア処理
void Scene::High_score()
{
	//ハイスコアより現在のスコアの方が大きいかどうか
	if (high_score < sum_score)
	{
		high_score = sum_score;
	}
}

//残り時間表示処理
void Scene::Time_Anim()
{
	//プログラム開始時間と現在の時間を比べて差をだしてどれぐらい時間がたったか計算する
	int now_count = GetNowCount() - startTime;

	//1000ms=1sec
	if (now_count >= 1000 * baisu)
	{
		time_set--;

		baisu++;
	}

	time_sec1 = time_set / 10;			//10の位

	time_sec2 = time_set % 10;			//1の位
}

//終了時処理
void Scene::Finalize()
{
	startTime = GetNowCount();		//プログラム開始時間

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

	//画像の削除
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(number[i]);
	}

	DeleteGraph(img_score);
	DeleteGraph(img_high_score);
	DeleteGraph(timer_img);

	DeleteSoundMem(stage_sound);
}

void Scene::Finish()
{

	//終了時処理を一度だけ実行
	if (Finalize_count == 0)
	{
		Finalize();

		Finalize_count = 1;

		PlaySoundMem(finish_se, DX_PLAYTYPE_BACK, TRUE);
	}

	//Finifh画像の描画
	DrawRotaGraphF(320, 240, 0.5, 0.0, finish_img, TRUE);

	//ここでサウンドを流す

	//プログラム開始時間と現在の時間を比べて差をだしてどれぐらい時間がたったか計算する
	int now_count = GetNowCount() - startTime;

	if (now_count >= 3000)
	{
		DeleteGraph(finish_img);

		//リザルトを一度だけ実行
			if (sum_score < 1000)		//BAD
			{
				DrawRotaGraphF(320, 240, 0.5, 0.0, result_img[0], TRUE);

				//SEを一度だけ実行
				if (se_count == 0)
				{
					PlaySoundMem(result_se[0], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (sum_score >= 1000 && sum_score < 1500)		//OK
			{
				DrawRotaGraphF(320, 240, 0.2, 0.0, result_img[1], TRUE);

				//SEを一度だけ実行
				if (se_count == 0)
				{
					PlaySoundMem(result_se[1], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (sum_score >= 1500 && sum_score < 3000)			//GOOD
			{
				DrawRotaGraphF(320, 240, 0.5, 0.0, result_img[2], TRUE);

				//SEを一度だけ実行
				if (se_count == 0)
				{
					PlaySoundMem(result_se[2], DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (sum_score >= 3000)			//PERFECT
			{
				DrawRotaGraphF(320, 240, 0.5, 0.0, result_img[3], TRUE);

				//SEを一度だけ実行
				if (se_count == 0)
				{
					PlaySoundMem(result_se[3], DX_PLAYTYPE_BACK, TRUE);
				}
			}

			se_count = 1;

		if (now_count >= 5000)
		{
			//リスタート処理
			DrawFormatString(200, 300, GetColor(0, 0, 0), "スペースキーを押してリスタート");
			if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
			{
				//終了時SEを止める
				StopSoundMem(finish_se);

				//現在のスコアが前回より高いか
				High_score();
			
				//初期化処理
				Initialize();
			}
		}
	}
	
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