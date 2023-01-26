#pragma once
#include "Model.h"
#include "MyMathUtility.h"

class Switch {
public:
	// ������
	void Initialize(Model* model, Vector3 pos);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

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
	Vector3 GetPosition() { return worldTransform_.translation_; }
	bool GetFlag() { return isFlag_; }
};