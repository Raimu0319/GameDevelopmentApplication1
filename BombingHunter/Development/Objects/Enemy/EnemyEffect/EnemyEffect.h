#pragma once
#include "../../GameObject.h"

class EnemyEffect : public GameObject
{
private:
	int animation_count;	//フレームカウント
	int toumeido;			//透明度を徐々に変化させる
	int shake;				//画像をがたがたさせる

public:
	int image;				//画像
	int filp_flag;			//反転フラグ

public:
	EnemyEffect();
	~EnemyEffect();

	void Initialize();			//初期化処理
	void Update();				//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了時処理	

	void MoveEffect();				//移動処理
	void SetImage(int img,int filp_flag);		//画像の取得処理
private:
	void EraseAnim();			//エネミーの削除処理
};
