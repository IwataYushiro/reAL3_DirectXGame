#pragma once
#include <sstream>

#include "DebugText.h"
#include "Switch.h"

class Stage {
public:
	// 列挙
	enum STAGE {
		NONE,		// 穴
		BLOCK,		// 地面, 壁
		SWITCH,	// スイッチ
		WALL,		// 消える壁
		GOAL,		// ゴール
	};

	// 構造体
	struct StageData {
		WorldTransform worldTransform_;	// 座標
		int type_;	// ブロックの種類
		int line_;
		int row_;
	};

private: // 定数
	static const int STAGE_WIDTH = 20;
	static const int STAGE_HEIGHT = 20;

public:
	// 初期化
	void Initialize(Model* model);

	// ステージ初期化
	void StageInitialize(const std::string stageNum);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// 座標ゲッター
	Vector3 GetBlockPosition(int line, int row);

private:
	// ステージ床の読み込み
	void LoadFloorBlock();

	// ステージファイル読み込み
	void LoadStageData(const std::string stageNum);

	// ステージ読み込み
	void LoadStageCommands();

	// ブロック初期化
	void InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row);

	// リストにブロックを追加
	void PushStageBlockList(std::list<std::unique_ptr<StageData>>& blocks_, int type, int line, int row, float depth);

private:
	// インプット
	Input* input_ = nullptr;
	// デバッグテキスト
	DebugText* debugText_ = nullptr;
	
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	int32_t textureHandle_ = 0u;

	// ファイルコマンド
	std::stringstream stageCommands;
	// ワールド変換データ
	std::list<std::unique_ptr<StageData>> stageBlocks_;
	std::list<std::unique_ptr<StageData>> floorBlocks_;

	// 倍率
	float magnification_ = 2.0f;
	// 半径
	float radius_ = 2.0f;

public: // アクセッサ
	// ゲッター
	float GetRadius() { return radius_; }
};