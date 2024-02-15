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

	int image_cathand;		//猫の手の画像
	int cathand_image;		//猫の手の画像を表示させるかどうか
	int cathand_move;		//猫の手の移動処理

	int image_bakuhatsu;	 //爆発エフェクト画像
	int bakuhatsu_image;	//エフェクトを表示させるかどうか
	int SetTime;

	int catbakuhatsu;       //エフェクトを表示する時間
	int cathand_count;		//猫の手を表示する時間

	bool is_active;			//有効状態か？
	int image;				//画像データ
	Vector2D location;		//位置座標
	Vector2D box_size;		//当たり判定の大きさ
	float angle;			//角度
	float speed;			//速さ
	float hp;				//体力
	float player_imagecount;//フレームごとにプレイヤー画像を変更する
	bool player_direction;  //プレイヤーの向き　0:左 1:右
	bool player_stun;       // プレイヤーがスタンしているかどうか
	//float fuel;					//燃料
	int barrier_count;		//バリアの枚数
	Barrier* barrier;		//バリア

	int barrier_SE;         //バリアのSE
	
public:
	Player();
	~Player();

	void Initialize();		//初期化処理
	void Update();			//更新処理
	void Draw();			//描画処理
	void Finalize();	//終了時処理

public:
	void SetActive(bool flg);		//有効フラグ設定
	void DecreaseHp(float value);	//体力減少処理
	Vector2D GetLocation() const;	//位置座標取得
	Vector2D GetBoxSize() const;	//当たり判定の大きさ取得
	float GetSpeed() const;			//速さ取得処理
	//float GetFuel() const;				//燃料取得
	float GetHp() const;				//体力取得
	int GetBarriarCount() const;	//バリアの枚数取得
	bool IsBarrier() const;				//バリアが有効か？を取得

	void Attack();						//攻撃判定処理
	void AttackEnd();					//攻撃判定処理		

private:
	void Movement();					//移動処理
	void Acceleration();				//加速処理
};
