#pragma once

class Time
{
private:
	//秒数カウント
	int time_count;
	//タイム画像
	int time[10];
	//タイマー画像
	int Timer_img;

	//時間設定
	int Time_set;
	
	//秒数画像表示
	int Time_sec1;
	int Time_sec2;

public:

	//コンストラクタ
	Time();
	~Time();

	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	//描画処理
	void Draw() const;

	//終了処理
	void Finalize();

public:
	//時間表示処理
	void Time_Anim();

};