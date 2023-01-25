#pragma once
#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "GlobalScene.h"
#include <cassert>
#include <list>
#include <memory>

class Player {
public:
	// �\����
	struct PieceData {
		WorldTransform worldTransform_;
		int type_;
	};

public:
	//������
  void Initialize(Model* model, Vector3 pos = {0.0f, 0.0f, 0.0f});

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection& viewProjection);

	//���Z�b�g����
	void Reset();

private:
	//�v���C���[�̈ړ�����
	void Move();

private:
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//��
	Audio* audio_ = nullptr;
	//�T�E���h�f�[�^
	uint32_t jumpSound_ = 0;

	// ���[���h�ϊ��f�[�^
	PieceData wt;
	// �R�X�g
	int cost_ = 5;

	//���S�t���O
	bool isDead_ = false;
	//�}�E�X
	bool mouseClick_;

public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
	int GetCost() { return cost_; }
};
