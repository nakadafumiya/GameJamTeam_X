#include "ResultScene.h"
#include "../Object/RankingData.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"


ResultScene::ResultScene() : back_ground(NULL), score(0), itemcount_result(0)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}

	for (int i = 0; i <4; i++)
	{
		ResultFont[i] = NULL;
	}
}

ResultScene::~ResultScene()
{

}

//初期化処理
void ResultScene::Initialize()
{
	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");
	int result = LoadDivGraph("Resource/images/items2.png", 3, 3, 1, 64, 64,
		enemy_image);
	ResultFont[0] = LoadGraph("Resource/images/Font_gameover.png");
	ResultFont[1] = LoadGraph("Resource/images/Font_gamescore.png");
	ResultFont[2] = LoadGraph("Resource/images/Font_rundistance.png");
	ResultFont[3] = LoadGraph("Resource/images/Font_Item.png");
	back_image = LoadGraph("Resource/images/BackImage.png");
	
	itemcount_result = 0;

	//エラーチェック
	if (back_ground == -1)
	{
		throw ("Resource/images/back.bmpがありません\n");
	}
	if (result == -1)
	{
		throw ("Resource/images/car.bmpがありません\n");
	}
	if (ResultFont[0] == -1)
	{
		throw ("Resource/images/Font_gemeover.pngがありません\n");
	}
	if (ResultFont[1] == -1)
	{
		throw ("Resource/images/Font_gamescore.pngがありません\n");
	}
	if (ResultFont[2] == -1)
	{
		throw ("Resource/images/Font_rundistance.pngがありません\n");
	}
	if (ResultFont[3] == -1)
	{
		throw ("Resource/images/Font_Item.pngがありません\n");
	}

	//ゲーム結果の読み込み
	ReadResultData();
}

//更新処理
eSceneType ResultScene::Update()
{
	// Bボタンでランキングに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_RANKING_INPUT;
	}

	return GetNowScene();

}

//描画処理
void ResultScene::Draw() const
{
	//背景画像を描画
	/*DrawGraph(0, 0, back_ground, TRUE);*/
	DrawGraph(0, 0, back_image, FALSE);

	//スコア等表示領域

	/*DrawBox(0, 0, 640, 480, GetColor(0, 153, 0), TRUE);*/
	
	/*DrawBox(100, 100, 540, 380, GetColor(0, 153, 0), TRUE);*/
	/*DrawBox(100, 100, 540, 380, GetColor(0, 0, 0), FALSE);*/

	
	
	DrawRotaGraph(320, 50, 0.5f, 0, ResultFont[0], TRUE);
	SetFontSize(25);
	//DrawString(180, 200, "走行距離　　　", GetColor(0, 0, 0));//<-
	DrawRotaGraph(180, 150, 0.29f, 0, ResultFont[2], TRUE);
	DrawFormatString(300, 140, GetColor(255, 255, 255), "%08d × １０", score / 10 - itemcount_result * 150);
	/*for (int i = 0; i < 3; i++)*/
	/*{
		DrawRotaGraph(230, 230 + (i * 20), 0.5f, 0, enemy_image[i],
TRUE);		
		DrawFormatString(260, 222 + (i * 21), GetColor(255, 255, 255), "%6d x%4d=%6d",
			enemy_count[i], (i + 1) * 50, (i + 1) * 50 * enemy_count[i]);
	}*/

	DrawRotaGraph(160, 218, 0.17f, 0, ResultFont[3], TRUE);
	DrawRotaGraph(280, 220, 1.0f, 0, enemy_image[0],
			TRUE);
	/*SetFontSize(25);*/
	DrawFormatString(270, 205, GetColor(255, 255, 255), "    = %d × １５０", itemcount_result);
	DrawRotaGraph(180, 320, 0.4f, 0, ResultFont[1], TRUE);
	SetFontSize(30);
	DrawFormatString(250, 310, 0xFFFFFF, "   = %6d", score);

	
	/*DrawString(180, 290, "スコア", GetColor(0, 0, 0));*/
	/*DrawFormatString(250, 333, 0xFFFFFF, "     =%6d", score);*/
}

//終了時処理
void ResultScene::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemy_image[i]);
	}
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読み込み
void ResultScene::ReadResultData()
{
	//fileオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw ("Resource/dat/result_data.csvが読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%6d,\n", &score);
	fscanf_s(fp, "%6d,\n", &itemcount_result);
	
	//避けた数と得点を取得
	for (int i = 0; i < 3; i++)
	{
		fscanf_s(fp, "%6d,\n", &enemy_count[i]);
	}

	//ファイルクローズ
	fclose(fp);
}