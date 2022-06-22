#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "PlayerBullet.h"
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
	void Move();

	//�v���C���[�̐��񏈗�
	void Rotate();
	
	//�v���C���[�̍U������
	void Attack();

	//�ړ���������
	void MoveLimit();

	//�`��
	void Draw(ViewProjection& viewProjection);

  private:
	//�e
	PlayerBullet* bullet_ = nullptr;  
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
