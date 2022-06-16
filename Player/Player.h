#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

class Player {
  public:
	Player();
	~Player();

	//������
	void Initialize(Model* model, uint32_t textureHandle);

	//�X�V
	void Update();

	//�v���C���[�̈ړ�����
	void PlayerMove();

	//�ړ���������
	void PlayerMoveLimit();

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
