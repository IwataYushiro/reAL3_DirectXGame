#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//�I�v�V����(�K���_���ł����t�@���l���݂�����)
class OptionBit {
  public:
	//������
	void Initialize(Model* model);

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection& viewprojection);

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

};
