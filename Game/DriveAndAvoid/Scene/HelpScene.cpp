#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include"DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���

	background_image = LoadGraph("Resource/images/BackImage.png");
	Help_Font = LoadGraph("Resource/images/Help_Font.png");
	Help_Cat = LoadGraph("Resource/images/Help_Cat.png");
	Help_Cat2 = LoadGraph("Resource/images/Help_Cat2.png");
	Help_HP= LoadGraph("Resource/images/Help_HP.png");
	Help_HP2= LoadGraph("Resource/images/Help_HP2.png");
	Help_Item = LoadGraph("Resource/images/Help_Item.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw ("Resource/images/Title.png������܂���\n");
	}

}

//�X�V����
eSceneType HelpScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();

}

//�`�揈��
void HelpScene:: Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);
	DrawGraph(200, 10, Help_Font, TRUE);
	DrawGraph(40, 200, Help_Cat, TRUE);
	DrawGraph(60, 320, Help_Cat2, TRUE);
	DrawGraph(100, 180, Help_HP, TRUE);
	DrawGraph(150, 310, Help_HP2, TRUE);
	DrawGraph(10, 350, Help_Item, TRUE);


	//�Q�[������
	SetFontSize(16);

	DrawString(160, 100, "�L�����𑀍삵�ăn�C�X�R�A��ڎw���I", 0xffffff, 0);
	DrawString(20, 180, "�����܂�𓥂ނƔL����񂪊����ă_���[�W����炤���I", 0xffffff, 0);
	DrawString(20, 300, "�L�ʂ�H�ׂĉ񕜂��悤�I", 0xffffff, 0);
	DrawString(300, 300, "�l�Y�~��|���ƃo���A���񕜁I", 0xffffff, 0);

	DrawString(150, 450, "----�@B�{�^���������ă^�C�g���֖߂�@----", 0xffffff, 0);

}

//�I��������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}
