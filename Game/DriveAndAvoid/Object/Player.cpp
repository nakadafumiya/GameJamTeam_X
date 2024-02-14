#include "Player.h"
#include "../Utility/InputControl.h"
#include"DxLib.h"

Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),
speed(0.0f), hp(0.0f),  barrier_count(0),player_direction(0),player_imagecount(0),player_stun(0),
barrier(nullptr)
{
	image_left1 = LoadGraph("Resource/images/catrun_left_1.png");
	image_left2 = LoadGraph("Resource/images/catrun_left_2.png");
	image_right1 = LoadGraph("Resource/images/catrun_right_1.png");
	image_right2 = LoadGraph("Resource/images/catrun_right_2.png");
	image_stun = LoadGraph("Resource/images/catstun.png");
	image_bakuhatsu = LoadGraph("Resource/images/bakuhatsu.png");
	image_cathand = LoadGraph("Resource/images/cathand2.png");

}

Player::~Player()
{


}

//����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(30.0f, 1.0f);
	angle = 0.0f;
	speed = 6.0f;
	hp = 1000;
	/*fuel = 20000;*/
	barrier_count = 3;

	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/catrun_left_1.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/catleft_1.png������܂���\n");
	}
}

//�X�V����
void Player::Update()
{
	// �Q�[������ɉ��Z����
	player_imagecount++;

	if (player_imagecount > 60)
	{
		player_imagecount = 0;
	}
	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		player_stun = 1;
		angle += DX_PI_F / 24.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			player_stun = 0;
			is_active = true;
		}
		return;
	}

	//�R���̏���
	/*fuel -= speed;*/

	//�ړ�����
	Movement();

	////����������
	//Acceleration();
	
	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && barrier_count > 0)
	{
		if(barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}

}

//�`�揈��
void Player::Draw()
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	

	//�o���A����������Ă�����A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}


	if (player_stun == 1)
	{
		image = image_stun;
	}

	if (player_imagecount < 30 && player_direction == 0 && player_stun != 1)
	{
		image = image_left1;
	}
	else if (player_imagecount > 29 && player_direction == 0 && player_stun != 1)
	{
		image = image_left2;
	}

	if (player_imagecount < 30 && player_direction == 1 && player_stun != 1)
	{
		image = image_right1;
	}
	else if (player_imagecount > 29 && player_direction == 1 && player_stun != 1)
	{
		image = image_right2;
	}

	//爆発エフェクトの表示時間設定
	if(bakuhatsu_image == true)
	{		
		catbakuhatsu++;
		if (catbakuhatsu > 5 && catbakuhatsu < 30)
		{
			DrawRotaGraph(location.x, location.y - 60, 0.8, angle, image_bakuhatsu, TRUE);
		}
		else if (catbakuhatsu > 30)
		{
			catbakuhatsu = 0;
			bakuhatsu_image = false;
		}
		
	}

	//猫の手のエフェクト時間設定
	if (cathand_image == true)
	{
		cathand_count++;
		cathand_move++;
		if (cathand_count < 5)
		{
			DrawRotaGraph((location.x - 100) + (cathand_move * 6), (location.y + 70) - (cathand_move * 6) , 1, 1, image_cathand, TRUE);
		}
		else if(cathand_count >=5 && cathand_count <= 10)
		{
			DrawRotaGraph(location.x - 50, location.y, 1, 1, image_cathand, TRUE);
		}
		else
		{
			cathand_count = 0;
			cathand_move = 0;
			cathand_image = false;
		}

	}

}

//�I��������
void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation() const
{
	return this->location;
}

//�����蔻��̑傫���擾����
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpeed() const
{
	return this->speed;
}

//�R���擾����
//float Player::GetFuel() const
//{
//	return this->fuel;
//}

//�̗͎擾����
float Player::GetHp() const
{
	return this->hp;
}

//�o���A�����擾����
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}

//�o���A�L�����H���擾
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		player_direction = 0;
		move += Vector2D(-2.0f, 0.0f);
		angle = -DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		player_direction = 1;
		move += Vector2D(2.0f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -2.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 2.0f);
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}

}

//攻撃判定処理
void Player::DrawHand()
{
	hand_image = true;	
}

void Player::AttackEnd()
{
//	hand_image = false;
}

////����������
//void Player::Acceleration()
//{
//	//LB�{�^���������ꂽ��A��������
//	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
//	{
//		speed -= 1.0f;
//	}
//
//	//RB�{�^���������ꂽ��A��������
//	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
//	{
//		speed += 1.0f;
//	}
//}