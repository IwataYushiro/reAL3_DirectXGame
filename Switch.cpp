#include "Switch.h"

void Switch::Initialize(Model* model, Vector3 pos) {
	// モデル読み込み
	model_ = model;

	// 座標コピー
	worldTransform_.translation_ = pos;
}

void Switch::Update() {

}

void Switch::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
