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

//初期化処理
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

	//画像の読み込み
	image = image_left1;

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/catrun_left_1.pngがありません\n");
	}
}

//更新処理
void Player::Update()
{
	// ゲーム中常時更新
	player_imagecount++;
	//操作不可状態であれば、自身を回転させる
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

	// プレイヤー画像の更新処理
	if (player_imagecount > 60 && is_active)
	{
		player_imagecount = 0;
	}

	////燃料の消費
	//fuel -= speed;

	//移動処理
	Movement();

	////加減速処理
	//Acceleration();
	
	/*if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}*/

	//バリア処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && barrier_count > 0)
	{
		if(barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}

	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤー画像の描画

	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//バリアが生成されていたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}

	// イメージカウントごとに、プレイヤー画像の表示を入れ替える
	// 左向き時の処理
	if (player_imagecount < 30 && player_direction == 0)
	{
		image = image_left1;
	}
	else if(player_imagecount > 29 && player_direction == 0)
	{
		image = image_left2;
	}

	// 右向きの処理
	if (player_imagecount < 30 && player_direction == 1)
	{
		image = image_right1;
	}
	else if (player_imagecount > 29 && player_direction == 1)
	{
		image = image_right2;
	}

	// スタン状態なら、描画を行う
	if (!is_active)
	{
		image = LoadGraph("Resource/images/catstun(2).png");
	}

}

//終了時処理
void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//当たり判定の大きさ取得処理
Vector2D Player::GetBoxSize() const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed() const
{
	return this->speed;
}

////燃料取得処理
//float Player::GetFuel() const
//{
//	return this->fuel;
//}

//体力取得処理
float Player::GetHp() const
{
	return this->hp;
}

//バリア枚数取得処理
int Player::GetBarriarCount() const
{
	return this->barrier_count;
}

//バリア有効か？を取得
bool Player::IsBarrier() const
{
	return (barrier != nullptr);
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//十字移動処理
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

	//画面外に行かないように制限する
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}

////加減速処理
//void Player::Acceleration()
//{
//	//LBボタンが押されたら、減速する
//	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
//	{
//		speed -= 1.0f;
//	}
//
//	//RBボタンが押されたら、加速する
//	if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
//	{
//		speed += 1.0f;
//	}
//}