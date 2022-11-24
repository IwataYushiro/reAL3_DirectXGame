#include "Pawn.h"
#include <cassert>

void Pawn::Initialize(Model* model, const Vector3& pos) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = pos;
}

void Pawn::Update() {
	// �s��X�V
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Pawn::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Pawn::GetWorldPosition() {
	//���[���h���W���擾
	Vector3 worldPos;

	// ���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}