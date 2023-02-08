#include "Switch.h"

void Switch::Initialize(Vector3 pos) {
	// モデル読み込み
	model_ = Model::Create();

	// 初期化
	worldTransform_.Initialize();
	// スケール設定
	worldTransform_.scale_ = { 1.0f, 1.0f, 1.0f };
	// 座標設定
	worldTransform_.translation_ = pos;
	// 行列更新
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
	worldTransform_.TransferMatrix();

	isFlag_ = false;
}

void Switch::Update() {

}

void Switch::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void Switch::OnCollisionSwitch() {
	isFlag_ = true;
}