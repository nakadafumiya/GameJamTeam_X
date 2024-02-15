#pragma once

#include "SceneBase.h"

class HelpScene : public SceneBase
{
private:
	int background_image; //背景画像
	int Help_Font;  //ヘルプフォント
	int Help_Cat; //説明用猫
	int Help_Cat2;//説明用猫2
	int Help_HP; //説明用HP
	int Help_HP2;//説明用HP
	int Help_Item;//説明用アイテム

	int button_SE[1];

public:
	HelpScene();
	virtual ~HelpScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

};
