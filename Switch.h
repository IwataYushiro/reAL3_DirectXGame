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

private:
	// �C���v�b�g
	Input* input_ = nullptr;

	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// ���[���h�ϊ��f�[�^


public: // �A�N�Z�b�T
};