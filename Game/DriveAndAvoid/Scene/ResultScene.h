#pragma once

#include "SceneBase.h"
#include "GameMainScene.h"

class ResultScene : public SceneBase
{
private:
	int back_ground;		//背景画像
	int score;					//スコア
	int enemy_count[3];			//敵のカウント
	int enemy_image[3];			//敵画像
	int ResultFont[3];				//リザルトのフォント画像
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