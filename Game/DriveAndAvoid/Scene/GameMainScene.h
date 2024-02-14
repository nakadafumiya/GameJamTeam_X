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
	int Font[2];		//フォント画像
	int enemy_image[3];		//敵画像
	int enemy_count[3];		//通り過ぎた敵カウント
	int Itemcount;			//アイテム取得時カウント
	int SE[2];				//サウンドエフェクト

	float hit;
	
	Player* player;			//プレイヤー
	Enemy** enemy;			//敵


	

	int MainBGM;       // BGM

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	//アイテムを取得した数
	/* int GetItemCount() const;*/
private:
	//ハイスコア読み込み処理
	void ReadHighScore();
	//当たり判定
	bool IsHitCheck(Player* p, Enemy* e);

	
};