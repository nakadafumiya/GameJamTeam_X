#include "GameMainScene.h"
#include "../Utility/InputControl.h"
#include "../Object/RankingData.h"
#include "DxLib.h"
#include <math.h>

/*
		//Ranking.csvbackup
20000,1,--------------,
10000,2,--------------,
 5000,3,--------------,
 1000,4,--------------,
  500,5,--------------,
*/



GameMainScene::GameMainScene() : high_score(0), back_ground(NULL),
barrier_image(NULL),MainBGM(0),
									mileage(0),player(nullptr),
enemy(nullptr)
{

	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		Itemcount[i] = NULL;
	}
	for (int i = 0; i < 4; i++)
	{
		Font[i] = NULL;
	}
	MainBGM = LoadSoundMem("Resource/music/CatRun.mp3");
	SE[0] = LoadSoundMem("Resource/music/catSE1.mp3");
	SE[1] = LoadSoundMem("Resource/music/catSE3_2.mp3");
	SE[2] = LoadSoundMem("Resource/music/catSE2.mp3");

	Punch_SE[0] = LoadSoundMem("Resource/SE/punch.mp3");
	Punch_SE[1] = LoadSoundMem("Resource/SE/punch2.mp3");

}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�����_�l��ǂݍ���
	ReadHighScore();

	//�摜�̓ǂݍ���
	barrier_image = LoadGraph("Resource/images/catbarrier.png");
	back_ground = LoadGraph("Resource/images/back.bmp");
	int result = LoadDivGraph("Resource/images/items2.png", 3, 3, 1, 64, 64,
		enemy_image);
	Font[0] = LoadGraph("Resource/images/Font_rundistance.png");
	Font[1] = LoadGraph("Resource/images/Font_highscore.png");
	Font[2] = LoadGraph("Resource/images/Font_Item.png");
	Font[3] = LoadGraph("Resource/images/Font_teki.png");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw ("Resource/images/back.bmp������܂���\n");
	}
	if (result == -1)
	{
		throw ("Resource/images/car.bmp������܂���\n");
	}
	if (barrier_image == -1)
	{
		throw ("Resource/images/barrier.png������܂���\n");
	}
	if (MainBGM == -1)
	{
		throw("Resource / music / CatRun.mp3が読み込まれませんでした\n");
	}

	//�I�u�W�F�N�g�̐���
	player = new Player;
	enemy = new Enemy * [10];

	//�I�u�W�F�N�g�̏�����
	player->Initialize();

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

	// BGMの再生
	ChangeVolumeSoundMem(200,MainBGM);
	ChangeVolumeSoundMem(200, SE[0]);
	ChangeVolumeSoundMem(200, SE[1]);

	ChangeVolumeSoundMem(250, Punch_SE[0]);
	ChangeVolumeSoundMem(250, Punch_SE[1]);

	PlaySoundMem(MainBGM, DX_PLAYTYPE_LOOP, TRUE);
				
}

//�X�V����
eSceneType GameMainScene::Update()
{

	//�v���C���[�̍X�V
	player->Update();

	//�ړ������̍X�V
	mileage += (int)player->GetSpeed() + 5;

	//�G��������
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] == nullptr)
			{
				int type = GetRand(20) % 20;
				if (type <= 10)
				{
					type = 1;
				}
				else if (type > 10 && type <= 15) 
				{
					type = 2;
				}
				else
				{
					type = 0;
				}

				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}
	
	//�G�̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player->GetSpeed());

			// ��ʊO�ɍs������A�G���폜���ăX�R�A���Z
			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}

			//�����蔻��̊m�F
			
			if (IsHitCheck(player, enemy[i]) && enemy[i]->GetType() == 0)
			{
				++Itemcount[0];
				PlaySoundMem(SE[0], DX_PLAYTYPE_BACK, TRUE);
				player->DecreaseHp(+50.0f);
				if (player->GetHp() > 1000) 
				{
					float pHp = player->GetHp();
					player->DecreaseHp(-(pHp - 1000));
				}
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}

			if (IsHitCheck(player, enemy[i]) && enemy[i]->GetType() == 1)
			{
				player->SetActive(false);
				player->DecreaseHp(-334.0f);
				if (player->GetHp() > 0.0f)
				{
					PlaySoundMem(SE[1], DX_PLAYTYPE_BACK, TRUE);
				}
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
			if (IsHitCheck(player, enemy[i]) && enemy[i]->GetType() == 2 && hit > 31)
			{

				if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
				{
					++Itemcount[1];
					player->Attack();

					RandomSE = GetRand(1) % 1;

					PlaySoundMem(Punch_SE[RandomSE], TRUE);

					enemy[i]->Finalize();
					delete enemy[i];
					enemy[i] = nullptr;
					player->GetBarriarCount();

				}

				//player->AttackEnd();

			}
			else if(IsHitCheck(player, enemy[i]) && enemy[i]->GetType() == 2 && hit < 31)
			{
				player->SetActive(false);
				player->DecreaseHp(-334.0f);
				if (player->GetHp() > 0.0f)
				{
					PlaySoundMem(SE[1], DX_PLAYTYPE_BACK, TRUE);
				}
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}

	}

	//�v���C���[�̔R�����̗͂�0�����Ȃ�A���U���g�ɑJ�ڂ���
	if (player->GetHp() < 0.0f)
	{
		DeleteSoundMem(MainBGM);

		return eSceneType::E_RESULT;
	}

	return GetNowScene();
}



//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);

	//�G�̕`��
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	//�v���C���[�̕`��
	player->Draw();

	//UI�̕`��
	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);
	SetFontSize(16);
	/*DrawFormatString(510, 20, GetColor(0, 0, 0), "�n�C�X�R�A");*/
	DrawRotaGraph(575, 20, 0.15f, 0, Font[1], TRUE);
	DrawFormatString(560, 40, GetColor(255, 255, 255), "%08d", high_score);
	/*DrawFormatString(510, 80, GetColor(0, 0, 0), "��������");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE,
			FALSE);

		DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d",
			enemy_count[i]);
	}*/

	/*DrawFormatString(510, 70, GetColor(0, 0, 0), "���s����");*/
	DrawRotaGraph(575, 70, 0.18f, 0, Font[0], TRUE);
	DrawFormatString(555, 90, GetColor(255, 255, 255), "%08d", mileage / 10);
	/*DrawFormatString(510, 240, GetColor(0, 0, 0), "�X�s�[�h");
	DrawFormatString(555, 260, GetColor(255, 255, 255), "%08.1f",
		player->GetSpeed());*/

	//�o���A�̖����̕`��
	for (int i = 0; i < player->GetBarriarCount(); i++)
	{
		DrawRotaGraph(520 + i * 48, 140, 0.23f, 0, barrier_image,
			TRUE, FALSE);
	}

	//�R���Q�[�W�̕`��
	/*float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy +
		40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(0, 0, 0),
		FALSE);*/

		//Itemの取得した数
	/*DrawFormatString(510, 190, GetColor(0, 0, 0), "GETしたアイテム数");*/
	DrawRotaGraph(570, 190, 0.14f, 0, Font[2], TRUE, FALSE);
	DrawRotaGraph(530, 230, 0.7f, 0, enemy_image[0], TRUE, FALSE);
	DrawRotaGraph(570, 280, 0.1f, 0, Font[3], TRUE, FALSE);
	DrawRotaGraph(530, 330, 0.7f, 0, enemy_image[2], TRUE, FALSE);
	SetFontSize(25);
	DrawFormatString(550, 213, GetColor(255, 255, 255), "X%d", Itemcount[0]);
	DrawFormatString(550, 317, GetColor(255, 255, 255), "X%d", Itemcount[1]);
	
	//�̗̓Q�[�W�̕`��
	float fx = 510.0f;
	float fy = 430.0f;
	SetFontSize(16);
	DrawFormatStringF(fx, fy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy +
		40.0f,GetColor(255, 0, 0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100, fy + 40.0f,
		GetColor(0, 0, 0), FALSE);

}

//�I��������
void GameMainScene::Finalize()
{
	
	//�X�R�A���v�Z����
	int score = (mileage / 10 * 10 + 150 * Itemcount[0] + 250 * Itemcount[1]);

		/*score += (i + 1) * 50 * enemy_count[i];*/
		/*score += 150 * Itemcount;*/
	
	//���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	//file�I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw ("Resource/dat/result_data.csv���J���܂���\n");
	}

	//�X�R�A��ۑ�
	fprintf(fp, "%d,\n", score);
	fprintf(fp, "%d,\n", Itemcount[0]);
	fprintf(fp, "%d,\n", Itemcount[1]);

	//���������Ɠ��_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d,\n", enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	delete[] enemy;

}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//�n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

//�����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	//�v���C���[���o���A��\���Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	//�G��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (e == nullptr)
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	hit = diff_location.y;

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) <
		box_ex.y));
}

//アイテム取得数処理
//int GameMainScene::GetItemCount() const
//{
//	return Itemcount;
//}