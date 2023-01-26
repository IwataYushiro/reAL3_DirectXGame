#include "Stage.h"
#include <cassert>
#include <fstream>

void Stage::Initialize(Model* model) {
	//シングルトンインスタンスを取得
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();

	// モデル読み込み
	model_ = model;

	// ステージの床を初期化
	LoadFloorBlock();
}

void Stage::StageInitialize(const std::string stageNum) {
	// 最初に残っている要素を削除
	stageBlocks_.clear();

	// バッファをクリア
	stageCommands.str("");
	// 状態をクリア
	stageCommands.clear(std::stringstream::goodbit);

	// ステージ用ファイル読み込み
	LoadStageData(stageNum);
	// ステージファイルで各要素を設定
	LoadStageCommands();
}

void Stage::Update() {
	// デバックテキスト
	/*debugText_->SetPos(0, 0);
	debugText_->Printf("%d, %d", stageLine_, stageRow_);*/
}

void Stage::Draw(ViewProjection viewProjection) {
	// ステージ描画
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		if (block->type_ == BLOCK) {
			model_->Draw(block->worldTransform_, viewProjection);
		}
	}
	// 床描画
	for (std::unique_ptr<StageData>& block : floorBlocks_) {
		model_->Draw(block->worldTransform_, viewProjection);
	}
}

void Stage::LoadStageData(const std::string stageNum) {
	// ファイル
	std::ifstream file;
	// パスを取得
	const std::string name = "stage";
	const std::string filename = name + stageNum + ".csv";
	const std::string directoryPath = "Resources/" + name + "/";
	// ファイルを開く
	file.open(directoryPath + filename);
	assert(file.is_open());
	// ファイルの内容を文字列ストリームにコピー
	stageCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void Stage::LoadStageCommands() {
	// 1行分の文字列を入れる変数
	std::string line;
	// マップチップ用変数
	int mapLine = 0;	// X
	int mapRow = 0;	// Y

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

		while (mapLine != STAGE_WIDTH) {
			// コマンド読み込み
			if (word.find("NONE") == 0 || word.find("0") == 0) {
				// ステージのブロックを追加
				PushStageBlockList(stageBlocks_, NONE, mapLine, mapRow, -10.0f);
				// インクリメント
				mapLine++;
			}
			else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
				// ステージのブロックを追加
				PushStageBlockList(stageBlocks_, BLOCK, mapLine, mapRow, -10.0f);
				// インクリメント
				mapLine++;
			}
			else if (word.find("SWITCH") == 0 || word.find("2") == 0) {
				// ステージのブロックを追加
				PushStageBlockList(stageBlocks_, SWITCH, mapLine, mapRow, -10.0f);
				// インクリメント
				mapLine++;
			}
			else if (word.find("WALL") == 0 || word.find("3") == 0) {
				// ステージのブロックを追加
				PushStageBlockList(stageBlocks_, WALL, mapLine, mapRow, -10.0f);
				// インクリメント
				mapLine++;
			}
			else if (word.find("SWITCH") == 0 || word.find("4") == 0) {
				// ステージのブロックを追加
				PushStageBlockList(stageBlocks_, SWITCH, mapLine, mapRow, -10.0f);
				// インクリメント
				mapLine++;
			}
			else if (word.find("WALL") == 0 || word.find("5") == 0) {
				// ステージのブロックを追加
				PushStageBlockList(stageBlocks_, WALL, mapLine, mapRow, -10.0f);
				// インクリメント
				mapLine++;
			}
			else if (word.find("GOAL") == 0 || word.find("6") == 0) {
				// ステージのブロックを追加
				PushStageBlockList(stageBlocks_, GOAL, mapLine, mapRow, -10.0f);
				// インクリメント
				mapLine++;
			}
			// 次の内容へ
			getline(line_stream, word, ',');
		}
		// マップチップLineが20を超えたらリセットしてRowをインクリメント
		if (mapLine == STAGE_WIDTH) {
			mapLine = 0;
			mapRow++;
		}
	}
}

void Stage::LoadFloorBlock() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			// ステージのブロックを追加
			PushStageBlockList(floorBlocks_, BLOCK, j, i, -14.0f);
		}
	}
}

void Stage::InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row) {
	// ワールドトランスフォームの初期化設定
	block->worldTransform_.Initialize();

	// スケール設定
	block->worldTransform_.scale_ = { magnification_, magnification_, magnification_ };
	// 座標設定
	block->worldTransform_.translation_ = pos;

	// 行列更新
	block->worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	block->worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(block->worldTransform_);
	block->worldTransform_.TransferMatrix();

	block->line_ = line;
	block->row_ = row;

}

void Stage::PushStageBlockList(std::list<std::unique_ptr<StageData>>& blocks_, int type, int line, int row, float depth) {
	// リストに入れるために新しく宣言
	std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();
	// ブロックの種類
	newBlock->type_ = type;
	// 座標
	Vector3 pos;
	pos.x = -38.0f + (4.0f * line);
	pos.y = depth;
	pos.z = 38.0f - (4.0f * row);

	// 初期化する
	InitializeStageBlock(newBlock, pos, line, row);
	// リストに追加
	blocks_.push_back(std::move(newBlock));
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