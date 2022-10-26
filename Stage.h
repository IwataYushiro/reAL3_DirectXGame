#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <sstream>

// 前方宣言
class Gimmick;

class Stage {
public:
	// 初期化
	void Initialize(Model* model, Gimmick* gimmick);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// ブロック初期化
	void StageBlockInitialize(Gimmick* gimmick);

	// ステージ読み込み
	void LoadStageData();

	// ステージ読み込み
	void LoadStageCommands();

public:
	// 列挙
	enum STAGE {
		NONE,			// 穴
		BLOCK,			// 床
		STEPUP,		// 段差上
		STEPDOWN,	// 段差下
		WALL,			// 壁
		END
	};

	// 構造体
	struct StageData {
		WorldTransform worldTransform_;
		int block_;
		int isGimmick_;
	};

	// ブロックの数
	static const int blockNum = 100;

private:
	// ワールド変換データ
	StageData stage_[blockNum];

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	int32_t textureHandle_ = 0u;

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	// 壁の高さ
	float wallHeight = 3.0f;

	// 段差の高さ
	float stepHeight = 1.0f;

	std::stringstream stageCommands;

	float radius = 5.0f;

	bool isEnd = false;

public:

	float GetRadius() { return radius; }

	Vector3 GetWorldPosition(int num) { return stage_[num].worldTransform_.translation_; }

	int GetBlock(int num) { return stage_[num].block_; }
	int GetEnd() { return isEnd; }
};

