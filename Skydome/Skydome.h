#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
//天球
class Skydome {
  public:
	//初期化
	void Initialize(Model* model);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewprojection);

  private:
	  //ワールド変換データ
	WorldTransform worldTransform_;

	  //モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
