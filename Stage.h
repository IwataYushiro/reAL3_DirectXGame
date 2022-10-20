#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>

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
		WALL,			// ��
		END
	};

	// �\����
	struct StageData {
		WorldTransform worldTransform_;
		int block_;
	};

	// �u���b�N�̐�
	static const int blockNum = 100;

private:
	// ���[���h�ϊ��f�[�^
	StageData stage_[blockNum];

	// ���f��
	Model* model_ = nullptr;

	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	// �ǂ̍���
	float wallHeight = 3.0f;

	// �i���̍���
	float stepHeight = 1.0f;

	std::stringstream stageCommands;

	float radius = 5.0f;

public:

	float GetRadius() { return radius; }

	Vector3 GetWorldPosition(int num) { return stage_[num].worldTransform_.translation_; }

	int GetBlock(int num) { return stage_[num].block_; }
};

