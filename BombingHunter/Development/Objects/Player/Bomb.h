#pragma once

//�L�[�{�[�h�̓��͏��Ǘ��N���X
class Bomb
{
private:
	//���N���X�̃|�C���^�i�A�h���X�̐�ɃC���X�^���X�𐶐�����j
	static Bomb* instance;

private:
	//�R���X�g���N�^��private�ɂ��邱�ƂŁA
	//���N���X�̃����o�֐��ł����C���X�^���X�𐶐��ł��Ȃ��悤�ɂ���
	Bomb() = default;

	//�R�s�[�K�[�h
	//�N���X�O�ŃC���X�^���X�𐶐����ēn�����Ƃ��ł��Ȃ��悤�ɂ���
	Bomb(Bomb& v) = delete;
	Bomb& operator = (const Bomb& v) = delete;
	//�`�R�s�[�K�[�h

public:
	~Bomb() = default;

public:
	//�C���X�^���X�擾���鏈��
	static Bomb* GetInstance();
	//�C���X�^���X�폜���鏈��
	static void DeleteInstance();

	//���菈��


public:
	//�L�[�{�[�h�̍X�V
	void Update();

	//���e�𐶐�
private:
	//�L�[�R�[�h�̗L���͈̓`�F�b�N
	bool CheckkeyCodeRange(int key_code) const;
};
