#pragma once

class Score
{
private:
	int score;
	int high_score;

public:
	//初期化処理
	void Initialize();

	//更新処理
	void Update();

	//描画処理
	void Draw() const;

	//終了時処理
	void Finalize();

public:
	//スコア加算処理
	void Score_count(int score);

};
