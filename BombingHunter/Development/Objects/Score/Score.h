#pragma once

class Score
{
private:
	int score;
	int high_score;

public:
	//����������
	void Initialize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw() const;

	//�I��������
	void Finalize();

public:
	//�X�R�A���Z����
	void Score_count(int score);

};
