#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"

class GameMainScene : public SceneBase
{
private:

	int high_score;			//�n�C�X�R�A
	int back_ground;	//�w�i�摜
	int barrier_image;		//�o���A�摜
	int mileage;			//���s����
	int Font[4];		//�t�H���g�摜
	int enemy_image[3];		//�G�摜
	int enemy_count[3];		//�ʂ�߂����G�J�E���g
	int Itemcount[2];			//�A�C�e���擾���J�E���g
	int SE[3];				//�T�E���h�G�t�F�N�g
	int Punch_SE[2];		//punch�T�E���h

	int RandomSE;




	float hit;
	
	Player* player;			//�E�v�E��E��E�C�E��E��E�[
	Enemy** enemy;			//�E�G


	

	int MainBGM;       // BGM

public:
	


	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	//�E�A�E�C�E�e�E��E��E��E��E�擾�E��E��E��E��E��E�
	/* int GetItemCount() const;*/
private:
	//�E�n�E�C�E�X�E�R�E�A�E�ǂݍ��E�ݏ��E��E�
	void ReadHighScore();
	//�E��E��E��E��E�蔻�E��E�
	bool IsHitCheck(Player* p, Enemy* e);

	
};