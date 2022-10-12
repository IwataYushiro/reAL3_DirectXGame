#include "Stage.h"
#include <fstream>

void Stage::Initialize(Model* model) {
	// モデル読み込み
	model_ = model;

	// ステージブロック読み込み
	LoadStageData();
	LoadStageCommands();

	// ワールドトランスフォームの初期設定
	for (StageData& stage : stage_) {
		// ブロックがNONEじゃなかったら初期化する
		if (stage.block_ != NONE) {
			stage.worldTransform_.Initialize();
			
			// スケール設定
			stage.worldTransform_.scale_ = { 5.0f, 5.0f, 3.0f };
		}
	}

	// 各ブロックの平行移動成分初期化
	StageBlockInitialize();
	
	// デバックテキスト
	debugText_ = DebugText::GetInstance();
}

// 更新
void Stage::Update() {
	Vector3 move = { 0.0f, 0.0f, -0.1f };
	
	for (StageData& stage : stage_) {
		if (stage.block_ != NONE) {
			stage.worldTransform_.translation_ += move;

			// 行列更新
			stage.worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
			stage.worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(stage.worldTransform_);

			stage.worldTransform_.TransferMatrix();
		}
	}
}

// 描画
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
	// ファイルを開く
	std::ifstream file;
	file.open("Resources/stage/stage1.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	stageCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void Stage::LoadStageCommands() {
	// 1行分の文字列を入れる変数
	std::string line;
	int num = 0;

	// コマンド実行ループ
	while (getline(stageCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を読み飛ばす
			continue;
		}

		// コマンド読み込み
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