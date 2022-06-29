#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//敵

class Enemy {
  public:
	Enemy();
	~Enemy();

	//初期化
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	//更新
	void Update();

	//描画
	void Draw(const ViewProjection& viewProjection);

  private:

	  //ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};

Enemy::Enemy() {}

Enemy::~Enemy() {}