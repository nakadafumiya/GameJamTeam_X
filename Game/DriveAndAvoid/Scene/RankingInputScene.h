#pragma once

#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingInputScene : public SceneBase
{
private:
	int background_image;	//�w�i�摜
	RankingData* ranking;	//�����L���O���
	int score;					//�X�R�A
	char name[15];				//���O
	int name_num;				//���O���͐�
	int cursor_x;				//�J�[�\���w���W
	int cursor_y;				//�J�[�\���x���W

public:
	RankingInputScene();
	virtual ~RankingInputScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	//���O���͏���
	bool InputName();
};