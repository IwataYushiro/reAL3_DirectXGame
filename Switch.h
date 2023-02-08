#pragma once
#include "Model.h"
#include "MyMathUtility.h"

class Switch {
public:
	// デストラクタ
	~Switch();

	// 初期化
	void Initialize(Vector3 pos);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// スイッチオン
	void OnCollisionSwitch();

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
	bool GetFlag() { return isFlag_; }
};