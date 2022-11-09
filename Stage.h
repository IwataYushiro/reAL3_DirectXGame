#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <sstream>
#include "GlobalScene.h"

class Stage {
public:
	// 列挙
	enum STAGE {
		NONE,			// 穴
		BLOCK,			// 地面
	};

	// 構造体
	struct StageData {
		WorldTransform worldTransform_;
		int type_;
	};

public:
	// 初期化
	void Initialize(Model* model, size_t scene);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// ブロック初期化
	void StageBlockInitialize(std::unique_ptr<StageData>& block, Vector3 pos);

	// ステージ読み込み
	void LoadStageData1();
	void LoadStageData2();
	void LoadStageData3();

	// ステージ読み込み
	void LoadStageCommands();

private:
	// ワールド変換データ
	std::list<std::unique_ptr<StageData>> stageBlock_;

	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	int32_t textureHandle_ = 0u;

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	std::stringstream stageCommands;

	// 倍率
	float five_ = 5.0f;

	float radius_ = 5.0f;
public: // アクセッサ
	//半径を返す
	float GetRadius() { return radius_; }
};

