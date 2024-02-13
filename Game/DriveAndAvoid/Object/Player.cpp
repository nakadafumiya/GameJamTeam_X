#include "Player.h"
#include "../Utility/InputControl.h"
#include"DxLib.h"

Player::Player() : is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),
speed(0.0f), hp(0.0f), /*fuel(0.0f),*/ barrier_count(0),player_imagecount(0.0),player_direction(0),
barrier(nullptr)
{
	image_left1 = LoadGraph("Resource/images/catrun_left1.png");
	image_left2 = LoadGraph("Resource/images/catrun_left2.png");
	image_right1 = LoadGraph("Resource/images/catrun_right1.png");
	image_right2 = LoadGraph("Resource/images/catrun_right2.png");
}

Player::~Player()
{


}

//����������
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 5.0f;
	hp = 1000;
	/*fuel = 20000;*/
	barrier_count = 3;

	//�摜�̓ǂݍ���
	image = image_left1;

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/catrun_left_1.png������܂���\n");
	}
}

//�X�V����
void Player::Update()
{
	// �Q�[�����펞�X�V
	player_imagecount++;
	//����s��Ԃł���΁A���g����]������
	if (!is_active)
	{
		player_imagecount = 0;
		angle += DX_PI_F / 24.0f;
		/*speed = 1.0f;*/
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	// �v���C���[�摜�̍X�V����
	if (player_imagecount > 60 && is_active)
	{
		player_imagecount = 0;
	}

	////�R���̏���
	//fuel -= speed;

	//�ړ�����
	Movement();

	////����������
	//Acceleration();
	
	/*if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}*/

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

	// �C���[�W�J�E���g���ƂɁA�v���C���[�摜�̕\�������ւ���
	// ���������̏���
	if (player_imagecount < 30 && player_direction == 0)
	{
		image = image_left1;
	}
	else if(player_imagecount > 29 && player_direction == 0)
	{
		image = image_left2;
	}

	// �E�����̏���
	if (player_imagecount < 30 && player_direction == 1)
	{
		image = image_right1;
	}
	else if (player_imagecount > 29 && player_direction == 1)
	{
		image = image_right2;
	}

	// �X�^����ԂȂ�A�`����s��
	if (!is_active)
	{
		image = LoadGraph("Resource/images/catstun(2).png");
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

////�R���擾����
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
		move += Vector2D(-1.0f, 0.0f);
		angle = -DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		player_direction = 1;
		move += Vector2D(1.0f, 0.0f);
		angle = DX_PI_F / 18;
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{

		move += Vector2D(0.0f, -1.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, 1.0f);
	}

	location += move;

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
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