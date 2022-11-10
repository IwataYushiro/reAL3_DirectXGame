#pragma once
#include "DebugText.h"
#include "Model.h"
#include "MyMathUtility.h"
#include <sstream>

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
	void Initialize(Model* model, const std::string stageNum);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// �u���b�N������
	void StageBlockInitialize(std::unique_ptr<StageData>& block, Vector3 pos);

	// �X�e�[�W�t�@�C���ǂݍ���
	void LoadStageData(const std::string stageNum);

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

	// �t�@�C���R�}���h
	std::stringstream stageCommands;

	// �N���A�t���O
	bool isClear_ = false;
	// �{��
	float five_ = 5.0f;
	// ���a
	float radius_ = 5.0f;

public: // �A�N�Z�b�T
	//���a��Ԃ�
	float GetRadius() { return radius_; }
	bool GetIsClear() { return isClear_; }
};

