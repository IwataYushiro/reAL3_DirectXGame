#include "Stage.h"
#include <fstream>
#include "Gimmick.h"

void Stage::Initialize(Model* model, Gimmick* gimmick) {
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
			stage.worldTransform_.scale_ = { 5.0f, 5.0f, 5.0f };
		}
		else {
			stage.worldTransform_.translation_ = { 0.0f, -100.0f, 0.0f };
		}
	}

	// �e�u���b�N�̕��s�ړ�����������
	StageBlockInitialize(gimmick);
	
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
			if (stage.block_ == END) {
				if(stage.worldTransform_.translation_.z <= -3.0f) {
					isEnd = true;
				}
			}
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

void Stage::StageBlockInitialize(Gimmick* gimmick) {
	// ����
	float height = 0.0f;

	for (int i = 0; i < blockNum; i++) {
		// �u���b�N�����ʒu
		stage_[i].worldTransform_.translation_ = { 0.0f,-24.0f, 10.0f * i };

		// �u���b�N���Ƃ̏�������
		if (stage_[i].block_ == BLOCK) {
			stage_[i].worldTransform_.translation_.y += height;
		}
		else if (stage_[i].block_ == STEPUP) {
			height += stepHeight;
			stage_[i].worldTransform_.translation_.y += height;
		}
		else if (stage_[i].block_ == STEPDOWN) {
			height -= stepHeight;
			stage_[i].worldTransform_.translation_ .y += height;
		}
		else if (stage_[i].block_ == WALL) {
			height += wallHeight;
			stage_[i].worldTransform_.translation_ .y += height;
		}
		else if (stage_[i].block_ == END) {
			stage_[i].worldTransform_.translation_.y += height;
		}
		else if (stage_[i].block_ == NONE) {

		}
		//
		if (stage_[i].isGimmick_ == 1) {
			Vector3 position = stage_[i].worldTransform_.translation_;
			position += Vector3(0.0f, 6.0f, 0.0f);
			gimmick->SetWorldPositionSpring(position);
		}
		else if (stage_[i].isGimmick_ == 2) {
			Vector3 position = stage_[i].worldTransform_.translation_;
			gimmick->SetPositionWaterFlow(position);
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
			getline(line_stream, word, ',');
			if (word.find("1") == 0) {
				stage_[num].isGimmick_ = 1;
			}
			else if (word.find("2") == 0) {
				stage_[num].isGimmick_ = 2;
			}
			num++;
		}
		else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
			stage_[num].block_ = BLOCK;
			getline(line_stream, word, ',');
			if (word.find("1") == 0) {
				stage_[num].isGimmick_ = 1;
			}
			else if (word.find("2") == 0) {
				stage_[num].isGimmick_ = 2;
			}
			num++;
		}
		else if (word.find("STEPUP") == 0 || word.find("2") == 0) {
			stage_[num].block_ = STEPUP;
			getline(line_stream, word, ',');
			if (word.find("1") == 0) {
				stage_[num].isGimmick_ = 1;
			}
			else if (word.find("2") == 0) {
				stage_[num].isGimmick_ = 2;
			}
			num++;
		}
		else if (word.find("STEPDOWN") == 0 || word.find("3") == 0) {
			stage_[num].block_ = STEPDOWN;
			getline(line_stream, word, ',');
			if (word.find("1") == 0) {
				stage_[num].isGimmick_ = 1;
			}
			else if (word.find("2") == 0) {
				stage_[num].isGimmick_ = 2;
			}
			num++;
		}
		else if (word.find("WALL") == 0 || word.find("4") == 0) {
			stage_[num].block_ = WALL;
			getline(line_stream, word, ',');
			if (word.find("1") == 0) {
				stage_[num].isGimmick_ = 1;
			}
			else if (word.find("2") == 0) {
				stage_[num].isGimmick_ = 2;
			}
			num++;
		}
		else if (word.find("END") == 0 || word.find("9") == 0) {
			stage_[num].block_ = END;
			num++;
			for (int i = num; i < blockNum; i++) {
				stage_[num].block_ = NONE;
			}
			break;
		}
	}
}