#pragma once

#include "Model.h"
#include "MyMathUtility.h"

class Knight {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	// モデル
	Model* model_;

	// ワールド変換行列
	WorldTransform worldTransform_;

	// 
public: //アクセッサ、インライン関数
	// 座標設定
	void SetPosition(const Vector3& pos) { worldTransform_.translation_ = pos; }
};