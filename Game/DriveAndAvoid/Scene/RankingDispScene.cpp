#include "RankingDispScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingDispScene::RankingDispScene() : background_image(NULL), ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}

//初期処理
void RankingDispScene::Initialize()
{
	WaitTime = 0;
	cnt = 0;
	//画像の読み込み
	button_SE[0] = LoadSoundMem("Resource/SE/button_2.mp3");
	ChangeVolumeSoundMem(100, button_SE[0]);

	background_image = LoadGraph("Resource/images/Ranking.png");



	//エラーチェック
	if (background_image == -1)
	{
		throw ("Resource/images/Ranking.bmpがありません\n");
	}

	//ランキング情報を取得
	ranking = new RankingData;
	ranking->Initialize();

}

//更新処理
eSceneType RankingDispScene::Update()
{
	//Aボタンが押されたあと、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_MAIN;
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(button_SE[0], TRUE);
		return eSceneType::E_TITLE;
	}

	WaitTime++;
	if (WaitTime > 60)
	{
		cnt++;
	}

	if (cnt == 4) 
		
	cnt = 0;
	WaitTime = 0;

	return GetNowScene();
}

//描画処理
void RankingDispScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	DrawGraph(0, 0, MovieGraphHandle, 1);
	//取得したランキングデータを描画する
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(180, 200 + i * 25, 0xffffff, "%2d %-15s %6d",
			ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));
	}
}

//終了時処理
void RankingDispScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);

	//動的メモリの開放
	ranking->Finalize();
	delete ranking;

}

//現在のシーン情報を取得
eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}