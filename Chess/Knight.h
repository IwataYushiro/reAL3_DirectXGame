#pragma once

#include "Model.h"
#include "MyMathUtility.h"

class Knight {
public:
	// ������
	void Initialize(Model* model);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

private:
	// ���f��
	Model* model_;

	// ���[���h�ϊ��s��
	WorldTransform worldTransform_;

	// 
public: //�A�N�Z�b�T�A�C�����C���֐�
	// ���W�ݒ�
	void SetPosition(const Vector3& pos) { worldTransform_.translation_ = pos; }
};