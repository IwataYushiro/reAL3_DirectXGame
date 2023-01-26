#pragma once
#include "Model.h"
#include "MyMathUtility.h"

class Switch {
public:
	// 初期化
	void Initialize(Model* model, Vector3 pos);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

private:
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	int32_t textureHandle_ = 0u;

	// ワールド変換データ
	WorldTransform worldTransform_;

	// フラグ
	bool isFlag_ = false;

public: // アクセッサ
	Vector3 GetPosition() { return worldTransform_.translation_; }
	bool GetFlag() { return isFlag_; }
};