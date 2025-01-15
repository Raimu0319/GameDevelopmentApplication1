#include "InGameScene.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/EnemyBase.h"
#include "../../Objects/Enemy/Kuribo.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include <fstream>

#define START_POINT		(3350.0f)
#define END_POINT		(-2700.0f)

InGameScene::InGameScene()
	: player(nullptr)
	, enemy(nullptr)
	, back_ground_image(NULL)
	, back_ground_sound(NULL)
	, e_count(0)
	, pause_flag(false)
	, location(0.0f,0.0f)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	// スクリーンオフセットを設定
	screen_offset.y = D_OBJECT_SIZE * 3.0f;
	screen_offset.x = 1688 * 2.0f;

	//カメラ座標の設定
	//screen_origin_position.x = (640 / 2);
	//screen_origin_position.y = (480 / 2);

	//screen_offestは描画だけを変えているから実際のlocationは変わらないはず
	player = CreateObject<Player>(Vector2D(-screen_offset.x, 60.0f));

	CreateObject<Kuribo>(Vector2D(-screen_offset.x + 200.f, 60.0f));

	//// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::CreateInstance();
	back_ground_image = rm->GetImages("Resource/Images/配置素材/NES---Super-Mario-Bros---World-1-1（修正版）.png")[0];
	//// BGMの読み込み
	//back_ground_sound = rm->GetSounds("Resource/Sounds/start-music.mp3");

	//PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
}

//入力処理
eSceneType InGameScene::Update(const float& delta_second)
{
	//入力情報の取得
	InputManager* input = InputManager::CreateInstance();

	//PAUSE画面への遷移
	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}

	//PAUSE画面ではなければ
	if (!pause_flag)
	{
		// 親クラスの更新処理を呼び出す
		__super::Update(delta_second);

		//// プレイヤーが死んだら、再スタート
		//if (player->GetDestroy())
		//{
		//	return eSceneType::re_start;
		//}
	}

	/*if (screen_offset.x > END_POINT)
	{
		if((player->GetLocation().x / 2) > )
		screen_offset.x -= 0.1f;
	}*/

	if (abs(player->GetLocation().x) > 640 / 2)
	{
		//screen_offset.x += 0.01f;
	}
	
	// シーン情報を返却する
	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	// 背景画像の描画
	//DrawRotaGraph(0, 480, 2.0, 0.0, back_ground_image, TRUE);

	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location.x + screen_offset.x;

	//float center = abs((graph_location.x / 2));
	//float p_loc = abs(player->GetLocation().x);

	//if (player != nullptr)
	//{
	//	if (p_loc > center)
	//	{
	//		
	//	}
	//}

	DrawRotaGraphF(graph_location.x, 480, 2.0, 0.0, back_ground_image, FALSE, FALSE);

	DrawFormatString(0, 90, GetColor(255, 255, 255), "%f", this->location.x);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	// UI系の描画処理
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="target">1つ目のゲームオブジェクト</param>
/// <param name="partner">2つ目のゲームオブジェクト</param>
void InGameScene::HitCheckObject(GameObject* target, GameObject* partner)
{
	// ヌルポチェック
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// 当たり判定情報を取得
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// 線分の始点と終点を設定する
		tc.box_location[0] = target->GetLocation();
		pc.box_location[0] = partner->GetLocation();

		// カプセル同士の当たり判定
		if (IsCheckCollision(tc, pc))
		{
			//二つのオブジェクトの距離を取得
			Vector2D lc_diff = target->GetLocation() - partner->GetLocation();

			//二つのオブジェクトの当たり判定の大きさを取得
			Vector2D box_size = target->GetBoxsize() + partner->GetBoxsize() / 2.0f;

			//距離より大きさが大きい場合、hit判定とする
			if ((fabsf(lc_diff.x) < box_size.x) && (fabs(lc_diff.y) < box_size.y))
			{
				//IsHitCheck(b1, b2);

				//当たったことをオブジェクトに通知する
				return true;
			}

			return false;

			tc.hitCheck = IsHitCheck(tc, pc);
			pc.hitCheck = IsHitCheck(pc, tc);

			target->SetCollision(tc.hitCheck.H_top, tc.hitCheck.H_bottom, tc.hitCheck.H_left, tc.hitCheck.H_right);
			partner->SetCollision(pc.hitCheck.H_top, pc.hitCheck.H_bottom, pc.hitCheck.H_left, pc.hitCheck.H_right);

			// 当たっていることを通知する
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}

}