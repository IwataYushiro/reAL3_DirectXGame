#pragma once
#include "Model.h"
#include "RailCamera.h"
#include "WorldTransform.h"
#include <cassert>
//�V��
class Skydome {
  public:
	~Skydome();
	//������
	void Initialize(Model* model);
	//���Z�b�g
	void Reset();
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

	//�J����
	RailCamera* railcamera_ = nullptr;
};
