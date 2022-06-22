#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

class Player {
  public:
	Player();
	~Player();

	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

	//更新
	void Update();

	//プレイヤーの移動処理
	void Move();

	//プレイヤーの旋回処理
	void Rotate();
	
	//プレイヤーの攻撃処理
	void Attack();

	//移動処理制限
	void MoveLimit();

	//描画
	void Draw(ViewProjection& viewProjection);

  private:
	//弾
	PlayerBullet* bullet_ = nullptr;  
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//インプット
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};
