#pragma once

template <class T>

class Singleton
{
protected:

	//コンストラクタをprivateにすることで、
	//自クラスのメンバ関数でしかインスタンスを生成できないようにする
	Singleton() = default;

	//コピーガード
	//クラス外でインスタンスを生成して渡すことができないようにする
	Singleton(Singleton& v) = delete;
	Singleton& operator = (const Singleton& v) = delete;
	//～コピーガード

public:
	~Singleton() = default;

	/// <summary>
	/// インスタンス削除処理
	/// </summary>
	//static void DeleteInstance();

public:	
	static T* CreateInstance()
	{
		//指定したクラスを生成する
		//staticはプログラムが終了するまで情報を持ち続けるやつ
		static T new_instance;

		return &new_instance;
	}
};