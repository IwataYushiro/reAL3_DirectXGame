#pragma once
#include "Model.h"
#include "MyMathUtility.h"

class Switch {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

private:
	// インプット
	Input* input_ = nullptr;

	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	int32_t textureHandle_ = 0u;

	// ワールド変換データ


public: // アクセッサ
};