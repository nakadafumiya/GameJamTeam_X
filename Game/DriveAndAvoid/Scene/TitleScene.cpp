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
	PlaySoundMem(title_BGM, DX_PLAYTYPE_LOOP, TRUE);
}

//�X�V����
eSceneType TitleScene::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
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
			StopSoundMem(title_BGM);
			return eSceneType::E_MAIN;
		case 1:
			StopSoundMem(title_BGM);
			return eSceneType::E_RANKING_DISP;
		case 2:
			StopSoundMem(title_BGM);
			return eSceneType::E_HELP;
		default:
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