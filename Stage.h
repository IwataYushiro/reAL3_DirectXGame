#pragma once
#include "DebugText.h"
#include "Model.h"
#include "MyMathUtility.h"
#include <sstream>

class Stage {
public:
	// 列挙
	enum STAGE {
		NONE,			// 穴
		BLOCK,			// 地面
	};

	// 構造体
	struct StageData {
		WorldTransform worldTransform_;	// 座標
		int type_;	// ブロックの種類
		int line_;	// 行 (X)
		int row_;	// 列 (Y)
	};

public:
	// 初期化
	void Initialize(Model* model, const std::string stageNum);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// ブロック初期化
	void InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row);

	// ステージファイル読み込み
	void LoadStageData(const std::string stageNum);

	// ステージ読み込み
	void LoadStageCommands();

	// 座標ゲッター
	Vector3 GetBlockPosition(int line, int row);

private:
	// インプット
	Input* input_ = nullptr;
	// デバッグテキスト
	DebugText* debugText_ = nullptr;
	
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	int32_t textureHandle_ = 0u;

	// ワールド変換データ
	std::list<std::unique_ptr<StageData>> stageBlocks_;

	// ステージ 行,列
	int stageLine_;
	int stageRow_;

	// ファイルコマンド
	std::stringstream stageCommands;

	// クリアフラグ
	bool isClear_ = false;
	// 倍率
	float five_ = 2.0f;
	// 半径
	float radius_ = 2.0f;

public: // アクセッサ
	//半径を返す
	float GetRadius() { return radius_; }
	bool GetIsClear() { return isClear_; }
	int GetStageLine() { return stageLine_; }
	int GetStageRow() { return stageRow_; }
};