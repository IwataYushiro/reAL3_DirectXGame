#include "Pawn.h"
#include <cassert>

void Pawn::Initialize(Model* model, const Vector3& pos) {
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = pos;
}

void Pawn::Update() {
	// 行列更新
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Pawn::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Pawn::GetWorldPosition() {
	//ワールド座標を取得
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}