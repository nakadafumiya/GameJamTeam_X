#pragma once

#include "SceneBase.h"
#include "GameMainScene.h"

class ResultScene : public SceneBase
{
private:
	int back_ground;		//�w�i�摜
	int score;					//�X�R�A
	int enemy_count[3];			//�G�̃J�E���g
	int enemy_image[3];			//�G�摜
	int ResultFont[3];				//���U���g�̃t�H���g�摜
	GameMainScene* item;	
public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void ReadResultData();
};