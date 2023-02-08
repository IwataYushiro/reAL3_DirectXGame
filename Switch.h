#pragma once
#include "Model.h"
#include "MyMathUtility.h"

class Switch {
public:
	// �f�X�g���N�^
	~Switch();

	// ������
	void Initialize(Vector3 pos);

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
};