#include "Stage.h"
#include <fstream>
#include "Gimmick.h"

void Stage::Initialize(Model* model, Gimmick* gimmick) {
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
			stage.worldTransform_.scale_ = { 5.0f, 5.0f, 5.0f };
		}
		else {
			stage.worldTransform_.translation_ = { 0.0f, -100.0f, 0.0f };
		}
	}

	// 各ブロックの平行移動成分初期化
	StageBlockInitialize(gimmick);
	
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
			if (stage.block_ == END) {
				if(stage.worldTransform_.translation_.z <= -3.0f) {
					isEnd = true;
				}
			}
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

void Stage::StageBlockInitialize(Gimmick* gimmick) {
	// 高さ
	float height = 0.0f;

	for (int i = 0; i < blockNum; i++) {
		// ブロック初期位置
		stage_[i].worldTransform_.translation_ = { 0.0f,-24.0f, 10.0f * i };

		// ブロックごとの条件分け
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