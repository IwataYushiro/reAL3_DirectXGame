#include "Stage.h"
#include <fstream>
#include "Gimmick.h"

void Stage::Initialize(Model* model, size_t scene) {
	// ���f���ǂݍ���
	model_ = model;
	LoadStageData1();
	// �X�e�[�W�u���b�N�ǂݍ���
	if (scene == stage1) {
		LoadStageData1();
	}
	else if (scene == stage2) {
		LoadStageData2();
	}
	else if (scene == stage3) {
		LoadStageData3();
	}
	LoadStageCommands();
	
	// �f�o�b�N�e�L�X�g
	debugText_ = DebugText::GetInstance();
}

// �X�V
void Stage::Update() {

}

// �`��
void Stage::Draw(ViewProjection viewProjection) {
	for (std::unique_ptr<StageData>& block : stageBlock_) {
		if (block->type_ != NONE) {
			model_->Draw(block->worldTransform_, viewProjection);
		}
	}
}

void Stage::StageBlockInitialize(std::unique_ptr<StageData>& block, Vector3 pos) {
	// ���[���h�g�����X�t�H�[���̏������ݒ�
	block->worldTransform_.Initialize();

	// �X�P�[���ݒ�
	block->worldTransform_.scale_ = { five_, five_, five_ };
	// ���W�ݒ�
	block->worldTransform_.translation_ = pos;

	// �s��X�V
	block->worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	block->worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(block->worldTransform_);
	block->worldTransform_.TransferMatrix();
}

void Stage::LoadStageData1() {
	// �t�@�C�����J��
	std::ifstream file;
	file.open("Resources/stage/stage1.csv");
	assert(file.is_open());

	// �t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	stageCommands << file.rdbuf();

	// �t�@�C�������
	file.close();
}

void Stage::LoadStageData2() {
	// �t�@�C�����J��
	std::ifstream file;
	file.open("Resources/stage/stage2.csv");
	assert(file.is_open());

	// �t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	stageCommands << file.rdbuf();

	// �t�@�C�������
	file.close();
}

void Stage::LoadStageData3() {
	// �t�@�C�����J��
	std::ifstream file;
	file.open("Resources/stage/stage3.csv");
	assert(file.is_open());

	// �t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	stageCommands << file.rdbuf();

	// �t�@�C�������
	file.close();
}

void Stage::LoadStageCommands() {
	// 1�s���̕����������ϐ�
	std::string line;

	// �R�}���h���s���[�v
	while (getline(stageCommands, line)) {
		// ���X�g�ɓ���邽�߂ɐV�����錾
		std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		// ������
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
			// NONE�͓ǂݔ�΂�
			continue;
		}
		else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
			newBlock->type_ = BLOCK;
			// x���W
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			// y���W
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			// z���W
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// ����������
			StageBlockInitialize(newBlock, Vector3(x, y, z));

			// ���X�g�ɒǉ�
			stageBlock_.push_back(std::move(newBlock));
		}
	}
}