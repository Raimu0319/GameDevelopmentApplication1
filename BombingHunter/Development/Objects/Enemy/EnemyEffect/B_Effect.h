#pragma once
#include "../../GameObject.h"

class B_Effect : public GameObject
{
private:
	int animation_count;	//�t���[���J�E���g
	int toumeido;			//�����x�����X�ɕω�������
	int	b_eff_img[3];		//�e�L�e�摜

public:
	int image;				//�摜
	int filp_flag;			//���]�t���O

public:
	B_Effect();
	~B_Effect();

	void Initialize();			//����������
	void Update();				//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I��������	
private:
	void AnimControl();			//�A�j���[�V��������
};
