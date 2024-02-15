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
	int Font[2];		//�t�H���g�摜
	int enemy_image[3];		//�G�摜
	int enemy_count[3];		//�ʂ�߂����G�J�E���g
	int SE[3];				//�T�E���h�G�t�F�N�g
	int Itemcount;			//�A�C�e���擾���J�E���g

	float hit;
	
	Player* player;			//�v���C���[
	Enemy** enemy;			//�G


	

	int MainBGM;       // BGM

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	//�A�C�e�����擾������
	/* int GetItemCount() const;*/
private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();
	//�����蔻��
	bool IsHitCheck(Player* p, Enemy* e);

	
};