#include "Switch.h"

void Switch::Initialize(Model* model, Vector3 pos) {
	// ���f���ǂݍ���
	model_ = model;

	// ���W�R�s�[
	worldTransform_.translation_ = pos;
}

void Switch::Update() {

}

void Switch::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
