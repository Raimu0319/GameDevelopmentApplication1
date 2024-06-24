#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Objects/Enemy/Enemy.h"
#include "Objects/Timer/Time.h"
#include "Scene/Scene.h"
#include "Scene/Stage.h"

//���C���֐��i�v���O�����͂�������n�܂�܂��B�j
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//Window���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y�i���F640px, �c�F480px�j��ݒ�
	SetGraphMode(640, 480, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		//�ُ��ʒm
		return -1;
	}

	//���[�J���ϐ���`
	Scene* scene = new Scene();			//�V�[�����
	Stage* stage = new Stage();			//�X�e�[�W���
	Time* time = new Time();			//���ԏ��
	int result = 0;							//�I����ԏ��

	//�`���𗠉�ʂ���n�߂�悤�Ɏw�肷��
	SetDrawScreen(DX_SCREEN_BACK);

	try
	{
		//�V�[���̏�����
		scene->Initialize();

		//�X�e�[�W�̏�����
		stage->Initialize();

		//���Ԃ̏�����
		time->Initialize();

		//���C�����[�v�i�E�B���h�E�ُ̈픭�� or�@ESC�L�[�������ꂽ��A���[�v�I���j
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) !=
			TRUE)
		{
			//���͋@�̂̍X�V
			InputControl::Update();

			//�V�[���̍X�V����
			scene->Update();

			//���ԍX�V����
			time->Update();

			//��ʂ̏�����
			ClearDrawScreen();

			//�X�e�[�W�̕`�揈��
			stage->Draw();

			//�V�[���̕`�揈��
			scene->Draw();

			//���Ԃ̕`�揈��
			time->Draw();

			//����ʂ̓��e��\��ʂɔ��f����
			ScreenFlip();

		}
	}
	catch (const char* error_log)
	{
		//�G���[����Log.txt�ɏo�͂���
		OutputDebugString(error_log);
		//�ُ��ԂɕύX����
		result = -1;
	}

	//�V�[�������폜����
	if (scene != nullptr)
	{
		scene->Finalize();
		stage->Finalize();
		time->Finalize();
		delete scene;
		delete stage;
		delete time;
		scene = nullptr;
		stage = nullptr;
		time = nullptr;
	}

	//DX���C�u�����̏I��������
	DxLib_End();

	//�I����Ԃ�ʒm
	return result;
}