#pragma once

#define D_PIVOT_CENTER		//���W�̌��_���摜�̒��S�ɂ���

class Stage 
{
private:
	int stage_image;
	int stage_sound;

public:
	Stage();
	~Stage();

	void Initialize() ;		//����������
	void Update();			//�X�V����
	void Draw() const ;		//�`�揈��
	void Finalize() ;		//�I��������
};
