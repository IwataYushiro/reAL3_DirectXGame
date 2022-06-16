#pragma once

#include "2d/DebugText.h"
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3d/ViewProjection.h"
#include "input/Input.h"
#include <cassert>

class Player {
  public:
	Player();
	~Player();

	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection);

  private:
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
#pragma once

#include "2d/DebugText.h"
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3d/ViewProjection.h"
#include "input/Input.h"
#include <cassert>

  class Player {
  public:
	Player();
	~Player();

	//初期化
	void Initialize(Model* model, uint32_t textureHandle);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection);

  private:
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