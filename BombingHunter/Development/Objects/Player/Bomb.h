#pragma once

//キーボードの入力情報管理クラス
class Bomb
{
private:
	//自クラスのポインタ（アドレスの先にインスタンスを生成する）
	static Bomb* instance;

private:
	//コンストラクタをprivateにすることで、
	//自クラスのメンバ関数でしかインスタンスを生成できないようにする
	Bomb() = default;

	//コピーガード
	//クラス外でインスタンスを生成して渡すことができないようにする
	Bomb(Bomb& v) = delete;
	Bomb& operator = (const Bomb& v) = delete;
	//～コピーガード

public:
	~Bomb() = default;

public:
	//インスタンス取得する処理
	static Bomb* GetInstance();
	//インスタンス削除する処理
	static void DeleteInstance();

	//判定処理


public:
	//キーボードの更新
	void Update();

	//爆弾を生成
private:
	//キーコードの有効範囲チェック
	bool CheckkeyCodeRange(int key_code) const;
};
