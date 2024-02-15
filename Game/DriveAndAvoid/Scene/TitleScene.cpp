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

//����������
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title.png");
	menu_image = LoadGraph("Resource/images/TitleFont.png");
	cursor_image = LoadGraph("Resource/images/nikukyuu.png");
	button_SE[0] = LoadSoundMem("Resource/SE/button.mp3");
	button_SE[1] = LoadSoundMem("Resource/SE/button_2.mp3");
	button_SE[2] = LoadSoundMem("Resource/SE/button_3.mp3");
	title_BGM = LoadSoundMem("Resource/music/Blue_Drops.mp3");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw ("Resource/images/Title.png������܂���\n");
	}
	if (menu_image == -1)
	{
		throw ("Resource/images/TitleFont.png������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw ("Resource/images/nikukyuu.png������܂���\n");
	}

	ChangeVolumeSoundMem(100, button_SE[0]);
	ChangeVolumeSoundMem(100, button_SE[1]);
	ChangeVolumeSoundMem(100, button_SE[2]);
	PlaySoundMem(title_BGM, DX_PLAYTYPE_LOOP, TRUE);
}

//�X�V����
eSceneType TitleScene::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{

		menu_cursor++;
		PlaySoundMem(button_SE[0], TRUE);

		//��ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		PlaySoundMem(button_SE[0], TRUE);

		//��ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
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

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//���j���|�摜�̕`��
	DrawGraph(200, 200, menu_image, TRUE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(180, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image,
		TRUE);
}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}