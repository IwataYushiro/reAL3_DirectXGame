#include "Stage.h"
#include <cassert>
#include <fstream>

void Stage::Initialize(Model* model, const std::string stageNum) {
	//シングルトンインスタンスを取得
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();

	// 最初に残っている要素を削除
	stageBlocks_.clear();

	// バッファをクリア
	stageCommands.str("");
	// 状態をクリア
	stageCommands.clear(std::stringstream::goodbit);

	// モデル読み込み
	model_ = model;

	// ステージ用ファイル読み込み
	LoadStageData(stageNum);
	// ステージファイルで各要素を設定
	LoadStageCommands();

	// 初期化
	stageLine_ = 1;
	stageRow_ = 1;

}

void Stage::Update() {
	// ブロック選択
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

	// デバックテキスト
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
	// ワールドトランスフォームの初期化設定
	block->worldTransform_.Initialize();

	// スケール設定
	block->worldTransform_.scale_ = { five_, five_, five_ };
	// 座標設定
	block->worldTransform_.translation_ = pos;

	// 行列更新
	block->worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	block->worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(block->worldTransform_);
	block->worldTransform_.TransferMatrix();

	// マップチップ用番号
	block->line_ = line;
	block->row_ = row;
}

void Stage::LoadStageData(const std::string stageNum) {
	// ファイルを開く
	std::ifstream file;

	const std::string name = "stage";
	const std::string filename = name + stageNum + ".csv";
	const std::string directoryPath = "Resources/" + name + "/";
	file.open(directoryPath + filename);

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

	// マップチップ用番号(列)
	int mapLine = 0;		// 行(X)左から
	int mapRow = 0;		// 列(Y)奥から

	// コマンド実行ループ
	while (getline(stageCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 文字列
		std::string word;

		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を読み飛ばす
			continue;
		}

		if (mapLine == 20) {
			mapLine = 0;
			mapRow++;
		}

		// コマンド読み込み
		while (mapLine != 20) {
			if (word.find("NONE") == 0 || word.find("0") == 0) {
				// NONEは読み飛ばす
				mapLine++;
			}
			else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
				// リストに入れるために新しく宣言
				std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

				// ブロックの種類
				newBlock->type_ = BLOCK;
				//// x座標
				//getline(line_stream, word, ',');
				//float x = (float)std::atof(word.c_str());
				//// y座標
				//getline(line_stream, word, ',');
				//float y = (float)std::atof(word.c_str());
				//// z座標
				//getline(line_stream, word, ',');
				//float z = (float)std::atof(word.c_str());

				//// マップチップ用番号(行)
				//getline(line_stream, word, ',');
				//int mapLine = (int)std::atoi(word.c_str());		// 行(X)

				// 座標
				Vector3 pos(-38.0f + (4.0f * mapLine), -10.0f, 38.0f - (4.0f * mapRow));

				// 初期化する
				InitializeStageBlock(newBlock, pos, mapLine, mapRow);

				// リストに追加
				stageBlocks_.push_back(std::move(newBlock));

				mapLine++;
			}
			else if (word.find("2") == 0) {
				mapLine++;
			}
			else if (word.find("3") == 0) {
				// リストに入れるために新しく宣言
				std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

				// ブロックの種類
				newBlock->type_ = BLOCK;

				// 座標
				Vector3 pos(-38.0f + (4.0f * mapLine), -10.0f, 38.0f - (4.0f * mapRow));

				// 初期化する
				InitializeStageBlock(newBlock, pos, mapLine, mapRow);

				// リストに追加
				stageBlocks_.push_back(std::move(newBlock));

				mapLine++;
			}
			else if (word.find("4") == 0) {
				mapLine++;
			}
			else if (word.find("5") == 0) {
				// リストに入れるために新しく宣言
				std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

				// ブロックの種類
				newBlock->type_ = BLOCK;

				// 座標
				Vector3 pos(-38.0f + (4.0f * mapLine), -10.0f, 38.0f - (4.0f * mapRow));

				// 初期化する
				InitializeStageBlock(newBlock, pos, mapLine, mapRow);

				// リストに追加
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
	// 範囲for
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		// 指定した番号に合った座標を返す
		if (block->line_ == line && block->row_ == row) {
			return block->worldTransform_.translation_;
		}
	}

	// なかったら0を返す
	return Vector3(0, 0, 0);
}