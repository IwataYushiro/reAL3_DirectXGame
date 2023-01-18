#include "Stage.h"
#include <cassert>
#include <fstream>

void Stage::Initialize(Model* model, const std::string stageNum) {
	//�V���O���g���C���X�^���X���擾
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();

	// �ŏ��Ɏc���Ă���v�f���폜
	stageBlocks_.clear();

	// �o�b�t�@���N���A
	stageCommands.str("");
	// ��Ԃ��N���A
	stageCommands.clear(std::stringstream::goodbit);

	// ���f���ǂݍ���
	model_ = model;

	// �X�e�[�W�p�t�@�C���ǂݍ���
	LoadStageData(stageNum);
	// �X�e�[�W�t�@�C���Ŋe�v�f��ݒ�
	LoadStageCommands();

	// ������
	stageLine_ = 1;
	stageRow_ = 1;

}

void Stage::Update() {
	// �u���b�N�I��
	if (input_->TriggerKey(DIK_UP) || input_->TriggerKey(DIK_DOWN) ||
		input_->TriggerKey(DIK_LEFT) || input_->TriggerKey(DIK_RIGHT)) {
		if (input_->TriggerKey(DIK_UP)) {
			stageRow_++;
		}
		else if (input_->TriggerKey(DIK_DOWN)) {
			stageRow_--;
		}
		if (input_->TriggerKey(DIK_RIGHT)) {
			stageLine_++;
		}
		else if (input_->TriggerKey(DIK_LEFT)) {
			stageLine_--;
		}
	}

	// �f�o�b�N�e�L�X�g
	debugText_->SetPos(0, 0);
	debugText_->Printf("%d, %d", stageLine_, stageRow_);
}

void Stage::Draw(ViewProjection viewProjection) {
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		if (block->type_ != NONE) {
			model_->Draw(block->worldTransform_, viewProjection);
		}
	}
}

void Stage::InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row) {
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

	// �}�b�v�`�b�v�p�ԍ�
	block->line_ = line;
	block->row_ = row;
}

void Stage::LoadStageData(const std::string stageNum) {
	// �t�@�C�����J��
	std::ifstream file;

	const std::string name = "stage";
	const std::string filename = name + stageNum + ".csv";
	const std::string directoryPath = "Resources/" + name + "/";
	file.open(directoryPath + filename);

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

	// �}�b�v�`�b�v�p�ԍ�(��)
	int mapLine = 0;		// �s(X)������
	int mapRow = 0;		// ��(Y)������

	// �R�}���h���s���[�v
	while (getline(stageCommands, line)) {
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

		if (mapLine == 20) {
			mapLine = 0;
			mapRow++;
		}

		// �R�}���h�ǂݍ���
		while (mapLine != 20) {
			if (word.find("NONE") == 0 || word.find("0") == 0) {
				// NONE�͓ǂݔ�΂�
				mapLine++;
			}
			else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
				// ���X�g�ɓ���邽�߂ɐV�����錾
				std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

				// �u���b�N�̎��
				newBlock->type_ = BLOCK;
				//// x���W
				//getline(line_stream, word, ',');
				//float x = (float)std::atof(word.c_str());
				//// y���W
				//getline(line_stream, word, ',');
				//float y = (float)std::atof(word.c_str());
				//// z���W
				//getline(line_stream, word, ',');
				//float z = (float)std::atof(word.c_str());

				//// �}�b�v�`�b�v�p�ԍ�(�s)
				//getline(line_stream, word, ',');
				//int mapLine = (int)std::atoi(word.c_str());		// �s(X)

				// ���W
				Vector3 pos(-38.0f + (4.0f * mapLine), -10.0f, 38.0f - (4.0f * mapRow));

				// ����������
				InitializeStageBlock(newBlock, pos, mapLine, mapRow);

				// ���X�g�ɒǉ�
				stageBlocks_.push_back(std::move(newBlock));

				mapLine++;
			}
			else if (word.find("2") == 0) {
				mapLine++;
			}
			else if (word.find("3") == 0) {
				// ���X�g�ɓ���邽�߂ɐV�����錾
				std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

				// �u���b�N�̎��
				newBlock->type_ = BLOCK;

				// ���W
				Vector3 pos(-38.0f + (4.0f * mapLine), -10.0f, 38.0f - (4.0f * mapRow));

				// ����������
				InitializeStageBlock(newBlock, pos, mapLine, mapRow);

				// ���X�g�ɒǉ�
				stageBlocks_.push_back(std::move(newBlock));

				mapLine++;
			}
			else if (word.find("4") == 0) {
				mapLine++;
			}
			else if (word.find("5") == 0) {
				// ���X�g�ɓ���邽�߂ɐV�����錾
				std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

				// �u���b�N�̎��
				newBlock->type_ = BLOCK;

				// ���W
				Vector3 pos(-38.0f + (4.0f * mapLine), -10.0f, 38.0f - (4.0f * mapRow));

				// ����������
				InitializeStageBlock(newBlock, pos, mapLine, mapRow);

				// ���X�g�ɒǉ�
				stageBlocks_.push_back(std::move(newBlock));

				mapLine++;
			}
			else if (word.find("6") == 0) {
				mapLine++;
			}
			getline(line_stream, word, ',');
		}
	}
}

Vector3 Stage::GetBlockPosition(int line, int row) {
	// �͈�for
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		// �w�肵���ԍ��ɍ��������W��Ԃ�
		if (block->line_ == line && block->row_ == row) {
			return block->worldTransform_.translation_;
		}
	}

	// �Ȃ�������0��Ԃ�
	return Vector3(0, 0, 0);
}