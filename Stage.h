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
		WorldTransform worldTransform_;	// ���W
		int type_;	// �u���b�N�̎��
		int line_;	// �s (X)
		int row_;	// �� (Y)
	};

public:
	// ������
	void Initialize(Model* model, const std::string stageNum);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// �u���b�N������
	void InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row);

	// �X�e�[�W�t�@�C���ǂݍ���
	void LoadStageData(const std::string stageNum);

	// �X�e�[�W�ǂݍ���
	void LoadStageCommands();

	// ���W�Q�b�^�[
	Vector3 GetBlockPosition(int line, int row);

private:
	// �C���v�b�g
	Input* input_ = nullptr;
	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// ���[���h�ϊ��f�[�^
	std::list<std::unique_ptr<StageData>> stageBlocks_;

	// �X�e�[�W �s,��
	int stageLine_;
	int stageRow_;

	// �t�@�C���R�}���h
	std::stringstream stageCommands;

	// �N���A�t���O
	bool isClear_ = false;
	// �{��
	float five_ = 2.0f;
	// ���a
	float radius_ = 2.0f;

public: // �A�N�Z�b�T
	//���a��Ԃ�
	float GetRadius() { return radius_; }
	bool GetIsClear() { return isClear_; }
	int GetStageLine() { return stageLine_; }
	int GetStageRow() { return stageRow_; }
};