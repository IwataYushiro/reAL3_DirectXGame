#include "Queen.h"
#include <cassert>

void Queen::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,0 };
}

void Queen::Update() {
	// 行列更新
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Queen::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Queen::GetWorldPosition() {
	//ワールド座標を取得
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}