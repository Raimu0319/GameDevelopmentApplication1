#pragma once
#include "GameObject.h"

class Character : public GameObject
{
public:
	Vector2D velocity = Vector2D(0.0f);		//速度

protected:
	int hit_point;							//残り残機
	std::vector<int> damage_animation;		//アニメーション画像
	bool on_ground;							//地面に触れているかどうか

protected:
	Character() : 
				velocity(0.0f)
			   ,hit_point(0)
			   ,on_ground(true)
	{

	}
	virtual ~Character()
	{
		this->Finalize();
	}

	/*/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset">オフセット値</param>
	virtual void Draw(const Vector2D& screen_offset) const;*/
	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize()
	{
		move_animation.clear();
	}


public:
	//virtual void OnHitCollision(GameObject*) override;
};