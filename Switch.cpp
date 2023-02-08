#include "Switch.h"

void Switch::Initialize(Vector3 pos) {
	// ���f���ǂݍ���
	model_ = Model::Create();

	// ������
	worldTransform_.Initialize();
	// �X�P�[���ݒ�
	worldTransform_.scale_ = { 1.0f, 1.0f, 1.0f };
	// ���W�ݒ�
	worldTransform_.translation_ = pos;
	// �s��X�V
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