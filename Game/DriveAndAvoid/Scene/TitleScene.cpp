#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

TitleScene::TitleScene() : background_image(NULL), menu_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Title.png");
	menu_image = LoadGraph("Resource/images/TitleFont.png");
	cursor_image = LoadGraph("Resource/images/nikukyuu.png");
	button_SE[0] = LoadSoundMem("Resource/SE/button.mp3");
	button_SE[1] = LoadSoundMem("Resource/SE/button_2.mp3");
	button_SE[2] = LoadSoundMem("Resource/SE/button_3.mp3");
	title_BGM = LoadSoundMem("Resource/music/Blue_Drops.mp3");

	//エラーチェック
	if (background_image == -1)
	{
		throw ("Resource/images/Title.pngがありません\n");
	}
	if (menu_image == -1)
	{
		throw ("Resource/images/TitleFont.pngがありません\n");
	}
	if (cursor_image == -1)
	{
		throw ("Resource/images/nikukyuu.pngがありません\n");
	}

	ChangeVolumeSoundMem(100, button_SE[0]);
	ChangeVolumeSoundMem(100, button_SE[1]);
	ChangeVolumeSoundMem(100, button_SE[2]);
	PlaySoundMem(title_BGM, DX_PLAYTYPE_LOOP, TRUE);
}

//更新処理
eSceneType TitleScene::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{

		menu_cursor++;
		PlaySoundMem(button_SE[0], TRUE);

		//一番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		PlaySoundMem(button_SE[0], TRUE);

		//一番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:
			PlaySoundMem(button_SE[2], TRUE);
			StopSoundMem(title_BGM);
			return eSceneType::E_MAIN;
		case 1:
			PlaySoundMem(button_SE[2], TRUE);
			StopSoundMem(title_BGM);
			return eSceneType::E_RANKING_DISP;
		case 2:
			PlaySoundMem(button_SE[2], TRUE);
			StopSoundMem(title_BGM);
			return eSceneType::E_HELP;
		default:
			PlaySoundMem(button_SE[2], TRUE);
			StopSoundMem(title_BGM);

			return eSceneType::E_END;

		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//メニュ－画像の描画
	DrawGraph(200, 200, menu_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(180, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image,
		TRUE);
}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}