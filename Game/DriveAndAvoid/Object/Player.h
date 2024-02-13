#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"

class Player
{
private:
	int image_left1;
	int image_left2;
	int image_right1;
	int image_right2;
	int image_stun;
	bool is_active;			//�L����Ԃ��H
	int image;				//�摜�f�[�^
	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//�����蔻��̑傫��
	float angle;			//�p�x
	float speed;			//����
	float hp;				//�̗�
	float player_imagecount;//�t���[�����ƂɃv���C���[�摜��ύX����
	bool player_direction;  //�v���C���[�̌����@0:�� 1:�E
	bool player_stun;       // �v���C���[���X�^�����Ă��邩�ǂ���
	//float fuel;					//�R��
	int barrier_count;		//�o���A�̖���
	Barrier* barrier;		//�o���A
	
public:
	Player();
	~Player();

	void Initialize();		//����������
	void Update();			//�X�V����
	void Draw();			//�`�揈��
	void Finalize();	//�I��������

public:
	void SetActive(bool flg);		//�L���t���O�ݒ�
	void DecreaseHp(float value);	//�̗͌�������
	Vector2D GetLocation() const;	//�ʒu���W�擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫���擾
	float GetSpeed() const;			//�����擾����
	//float GetFuel() const;				//�R���擾
	float GetHp() const;				//�̗͎擾
	int GetBarriarCount() const;	//�o���A�̖����擾
	bool IsBarrier() const;				//�o���A���L�����H���擾

private:
	void Movement();					//�ړ�����
	void Acceleration();				//��������
};
