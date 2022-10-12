#include "Stage.h"
#include <fstream>

void Stage::Initialize(Model* model) {
	// ���f���ǂݍ���
	model_ = model;

	// �X�e�[�W�u���b�N�ǂݍ���
	LoadStageData();
	LoadStageCommands();

	// ���[���h�g�����X�t�H�[���̏����ݒ�
	for (StageData& stage : stage_) {
		// �u���b�N��NONE����Ȃ������珉��������
		if (stage.block_ != NONE) {
			stage.worldTransform_.Initialize();
			
			// �X�P�[���ݒ�
			stage.worldTransform_.scale_ = { 5.0f, 5.0f, 3.0f };
		}
	}

	// �e�u���b�N�̕��s�ړ�����������
	StageBlockInitialize();
	
	// �f�o�b�N�e�L�X�g
	debugText_ = DebugText::GetInstance();
}

// �X�V
void Stage::Update() {
	Vector3 move = { 0.0f, 0.0f, -0.1f };
	
	for (StageData& stage : stage_) {
		if (stage.block_ != NONE) {
			stage.worldTransform_.translation_ += move;

			// �s��X�V
			stage.worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
			stage.worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(stage.worldTransform_);

			stage.worldTransform_.TransferMatrix();
		}
	}
}

// �`��
void Stage::Draw(ViewProjection viewProjection) {
	for (StageData& stage : stage_) {
		if (stage.block_ != NONE) {
			model_->Draw(stage.worldTransform_, viewProjection);
		}
	}
}

void Stage::StageBlockInitialize() {
	for (int i = 0; i < blockNum; i++) {
		if (stage_[i].block_ == BLOCK) {
			stage_[i].worldTransform_.translation_ = { 0.0f,-24.0f, 6.0f * i };
		}
		else if (stage_[i].block_ == STEPUP) {
			stage_[i].worldTransform_.translation_ = stage_[i - 1].worldTransform_.translation_;
			stage_[i].worldTransform_.translation_ += stepHeight;
		}
		else if (stage_[i].block_ == STEPDOWN) {
			stage_[i].worldTransform_.translation_ = stage_[i - 1].worldTransform_.translation_;
			stage_[i].worldTransform_.translation_ -= stepHeight;
		}
		else if (stage_[i].block_ == WALL) {
			stage_[i].worldTransform_.translation_ = stage_[i - 1].worldTransform_.translation_;
			stage_[i].worldTransform_.translation_ += wallHeight;
		}
	}
}

void Stage::LoadStageData() {
	// �t�@�C�����J��
	std::ifstream file;
	file.open("Resources/stage/stage1.csv");
	assert(file.is_open());

	// �t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	stageCommands << file.rdbuf();

	// �t�@�C�������
	file.close();
}

void Stage::LoadStageCommands() {
	// 1�s���̕����������ϐ�
	std::string line;
	int num = 0;

	// �R�}���h���s���[�v
	while (getline(stageCommands, line)) {
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		std::string word;
		// ,��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');

		// "//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			// �R�����g�s��ǂݔ�΂�
			continue;
		}

		// �R�}���h�ǂݍ���
		if (word.find("NONE") == 0 || word.find("0") == 0) {
			stage_[num].block_ = NONE;
			num++;
		}
		else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
			stage_[num].block_ = BLOCK;
			num++;
		}
		else if (word.find("STEPUP") == 0 || word.find("2") == 0) {
			stage_[num].block_ = STEPUP;
			num++;
		}
		else if (word.find("STEPDOWN") == 0 || word.find("3") == 0) {
			stage_[num].block_ = STEPDOWN;
			num++;
		}
		else if (word.find("WALL") == 0 || word.find("4") == 0) {
			stage_[num].block_ = WALL;
			num++;
		}
		else if (word.find("END") == 0 || word.find("9") == 0) {
			for (int i = num; i < blockNum; i++) {
				stage_[num].block_ = NONE;
			}
			break;
		}
	}
}