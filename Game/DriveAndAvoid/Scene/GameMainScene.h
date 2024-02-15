#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"

class GameMainScene : public SceneBase
{
private:

	int high_score;			//ハイスコア
	int back_ground;	//背景画像
	int barrier_image;		//バリア画像
	int mileage;			//走行距離
	int Font[4];		//フォント画像
	int enemy_image[3];		//敵画像
	int enemy_count[3];		//通り過ぎた敵カウント
	int Itemcount[2];			//アイテム取得時カウント
	int SE[3];				//サウンドエフェクト
	int Punch_SE[2];		//punchサウンド

	int RandomSE;




	float hit;
	
	Player* player;			//・ｽv・ｽ・ｽ・ｽC・ｽ・ｽ・ｽ[
	Enemy** enemy;			//・ｽG


	

	int MainBGM;       // BGM

public:
	


	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	//・ｽA・ｽC・ｽe・ｽ・ｽ・ｽ・ｽ・ｽ謫ｾ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
	/* int GetItemCount() const;*/
private:
	//・ｽn・ｽC・ｽX・ｽR・ｽA・ｽﾇみ搾ｿｽ・ｽﾝ擾ｿｽ・ｽ・ｽ
	void ReadHighScore();
	//・ｽ・ｽ・ｽ・ｽ・ｽ阡ｻ・ｽ・ｽ
	bool IsHitCheck(Player* p, Enemy* e);

	
};