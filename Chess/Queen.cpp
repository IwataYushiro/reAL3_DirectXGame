#include "Queen.h"
#include <cassert>

void Queen::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,0 };
}

void Queen::Update() {
	// �s��X�V
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Queen::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Queen::GetWorldPosition() {
	//���[���h���W���擾
	Vector3 worldPos;

	// ���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}