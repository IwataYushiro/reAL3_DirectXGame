#pragma once
#include "Model.h"
#include "MyMathUtility.h"

class Switch {
public:
	// ������
	void Initialize(Model* model);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// �X�C�b�`�I��
	void OnCollisionSwitch();

private:
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// �t���O
	bool isFlag_ = false;

public: // �A�N�Z�b�T
	bool GetFlag() { return isFlag_; }
	void SetPosition(Vector3 pos) {
		// ������
		worldTransform_.Initialize();
		// �X�P�[���ݒ�
		worldTransform_.scale_ = { 2.0f, 2.0f, 2.0f };
		// ���W�ݒ�
		worldTransform_.translation_ = pos;
		// �s��X�V
		worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
		worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
		worldTransform_.TransferMatrix();
	}
};