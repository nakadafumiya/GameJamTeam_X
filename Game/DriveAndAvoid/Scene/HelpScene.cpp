#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include"DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/BackImage.png");
	Help_Font = LoadGraph("Resource/images/Help_Font.png");
	Help_Cat = LoadGraph("Resource/images/Help_Cat.png");
	Help_Cat2 = LoadGraph("Resource/images/Help_Cat2.png");
	Help_HP= LoadGraph("Resource/images/Help_HP.png");
	Help_HP2= LoadGraph("Resource/images/Help_HP2.png");
	Help_Item = LoadGraph("Resource/images/Help_Item.png");
	//エラーチェック
	if (background_image == -1)
	{
		throw ("Resource/images/Title.bmpがありません\n");
	}

}

//更新処理
eSceneType HelpScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();

}

//描画処理
void HelpScene:: Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);
	DrawGraph(200, 10, Help_Font, TRUE);
	DrawGraph(40, 200, Help_Cat, TRUE);
	DrawGraph(60, 320, Help_Cat2, TRUE);
	DrawGraph(100, 180, Help_HP, TRUE);
	DrawGraph(150, 310, Help_HP2, TRUE);
	DrawGraph(10, 350, Help_Item, TRUE);


	//ゲーム説明
	SetFontSize(16);

	DrawString(160, 100, "猫ちゃんを操作してハイスコアを目指せ！", 0xffffff, 0);
	DrawString(20, 180, "水たまりを踏むと猫ちゃんが滑ってダメージを喰らうぞ！", 0xffffff, 0);
	DrawString(20, 300, "猫缶を食べて回復しよう！", 0xffffff, 0);
	DrawString(300, 300, "ネズミを倒すとバリアが回復！", 0xffffff, 0);

	DrawString(150, 450, "----　Bボタンを押してタイトルへ戻る　----", 0xffffff, 0);

}

//終了時処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}
