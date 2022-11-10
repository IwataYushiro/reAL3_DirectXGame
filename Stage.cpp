#include "Stage.h"
#include <cassert>
#include <fstream>

void Stage::Initialize(Model* model, const std::string stageNum) {
	// 最初に残っている要素を削除
	stageBlock_.clear();

	// モデル読み込み
	model_ = model;

	// ステージ用ファイル読み込み
	LoadStageData(stageNum);
	// ステージファイルで各要素を設定
	LoadStageCommands();

	// デバックテキスト
	debugText_ = DebugText::GetInstance();
}

void Stage::Update() {
}

void Stage::Draw(ViewProjection viewProjection) {
	for (std::unique_ptr<StageData>& block : stageBlock_) {
		if (block->type_ != NONE) {
			model_->Draw(block->worldTransform_, viewProjection);
		}
	}
}

void Stage::StageBlockInitialize(std::unique_ptr<StageData>& block, Vector3 pos) {
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

	// コマンド実行ループ
	while (getline(stageCommands, line)) {
		// リストに入れるために新しく宣言
		std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();

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

		// コマンド読み込み
		if (word.find("NONE") == 0 || word.find("0") == 0) {
			// NONEは読み飛ばす
			continue;
		}
		else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
			newBlock->type_ = BLOCK;
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 初期化する
			StageBlockInitialize(newBlock, Vector3(x, y, z));

			// リストに追加
			stageBlock_.push_back(std::move(newBlock));
		}
	}
}