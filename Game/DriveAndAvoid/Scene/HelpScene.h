#pragma once

#include "SceneBase.h"

class HelpScene : public SceneBase
{
private:
	int background_image; //�w�i�摜
	int Help_Font;  //�w���v�t�H���g
	int Help_Cat; //�����p�L
	int Help_Cat2;//�����p�L2
	int Help_HP; //�����pHP
	int Help_HP2;//�����pHP
	int Help_Item;//�����p�A�C�e��

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
