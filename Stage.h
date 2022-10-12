#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

#include <sstream>

class Stage {
public:
	// ������
	void Initialize(Model* model);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// �u���b�N������
	void StageBlockInitialize();

	// �X�e�[�W�ǂݍ���
	void LoadStageData();

	// �X�e�[�W�ǂݍ���
	void LoadStageCommands();

public:
	// ��
	enum STAGE {
		NONE,			// ��
		BLOCK,			// ��
		STEPUP,		// �i����
		STEPDOWN,	// �i����
		WALL			// ��
	};

	// �\����
	struct StageData {
		WorldTransform worldTransform_;
		int block_;
	};

private:
	// �u���b�N�̐�
	static const int blockNum = 100;

	// ���[���h�ϊ��f�[�^
	StageData stage_[blockNum];

	// ���f��
	Model* model_ = nullptr;

	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	// �ǂ̍���
	Vector3 wallHeight = { 0.0f, 3.0f, 6.0f };

	// �i���̍���
	Vector3 stepHeight = { 0.0f, 1.0f, 6.0f };

	std::stringstream stageCommands;
};

