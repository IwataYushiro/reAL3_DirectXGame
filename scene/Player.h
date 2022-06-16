#pragma once

#include "2d/DebugText.h"
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3d/ViewProjection.h"
#include "input/Input.h"
#include <cassert>

class Player {
  public:
	Player();
	~Player();

	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection& viewProjection);

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};
#pragma once

#include "2d/DebugText.h"
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3d/ViewProjection.h"
#include "input/Input.h"
#include <cassert>

  class Player {
  public:
	Player();
	~Player();

	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection& viewProjection);

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};