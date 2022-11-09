#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <sstream>
#include "GlobalScene.h"

class Stage {
public:
	// ��
	enum STAGE {
		NONE,			// ��
		BLOCK,			// �n��
	};

	// �\����
	struct StageData {
		WorldTransform worldTransform_;
		int type_;
	};

public:
	// ������
	void Initialize(Model* model, size_t scene);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// �u���b�N������
	void StageBlockInitialize(std::unique_ptr<StageData>& block, Vector3 pos);

	// �X�e�[�W�ǂݍ���
	void LoadStageData1();
	void LoadStageData2();
	void LoadStageData3();

	// �X�e�[�W�ǂݍ���
	void LoadStageCommands();

private:
	// ���[���h�ϊ��f�[�^
	std::list<std::unique_ptr<StageData>> stageBlock_;

	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	std::stringstream stageCommands;

	// �{��
	float five_ = 5.0f;

	float radius_ = 5.0f;
public: // �A�N�Z�b�T
	//���a��Ԃ�
	float GetRadius() { return radius_; }
};

