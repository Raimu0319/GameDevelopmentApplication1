#include "Time.h"
#include "DxLib.h"

Time::Time() : time_count(0), Time_set(0), Time_sec1(0), Time_sec2(0), Timer_img(NULL)
{

}

Time::~Time()
{
	//忘れ防止
	Finalize();
}

void Time::Initialize()
{
	//初期画像の読み込み
	time[0] = LoadGraph("Resource/Images/Score/0.png");
	time[1] = LoadGraph("Resource/Images/Score/1.png");
	time[2] = LoadGraph("Resource/Images/Score/2.png");
	time[3] = LoadGraph("Resource/Images/Score/3.png");
	time[4] = LoadGraph("Resource/Images/Score/4.png");
	time[5] = LoadGraph("Resource/Images/Score/5.png");
	time[6] = LoadGraph("Resource/Images/Score/6.png");
	time[7] = LoadGraph("Resource/Images/Score/7.png");
	time[8] = LoadGraph("Resource/Images/Score/8.png");
	time[9] = LoadGraph("Resource/Images/Score/9.png");

	Timer_img = LoadGraph("Resource/Images/TimeLimit/timer-03.png");

	//エラーチェック
	for (int i = 0; i < 10; i++)
	{
		if (time[i] == -1)
		{
			throw("時間表示画像がありません\n");
		}
	}

	//初期時間の設定
	Time_set = 60;

	//10の位
	Time_sec1 = Time_set / 10;
	//1の位
	Time_sec2 = Time_set % 10;
}

void Time::Update()
{
	Time_Anim();
}

void Time::Draw() const
{
	//タイマー画像
	DrawRotaGraphF(20, 460, 0.5, 0.0, Timer_img, TRUE);
	//秒数表示
	DrawRotaGraphF(45, 460, 1.0, 0.0, time[Time_sec1], TRUE);
	DrawRotaGraphF(60, 460, 1.0, 0.0, time[Time_sec2], TRUE);
}

void Time::Finalize()
{
	//画像の削除
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(time[i]);
	}	

	DeleteGraph(Timer_img);
}

//残り時間表示処理
void Time::Time_Anim()
{
	time_count++;

	//PCが144FPSだからフレームが144回動いたら一秒として処理する
	if (time_count >= 144)
	{

		Time_set--;

		//10の位
		Time_sec1 = Time_set / 10;
		//1の位
		Time_sec2 = Time_set % 10;

		time_count = 0;
	}

}
