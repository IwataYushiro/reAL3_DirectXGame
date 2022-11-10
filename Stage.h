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
		WorldTransform worldTransform_;
		int type_;
	};

public:
	// 初期化
	void Initialize(Model* model, const std::string stageNum);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection viewProjection);

	// ブロック初期化
	void StageBlockInitialize(std::unique_ptr<StageData>& block, Vector3 pos);

	// ステージファイル読み込み
	void LoadStageData(const std::string stageNum);

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

	// ファイルコマンド
	std::stringstream stageCommands;

	// クリアフラグ
	bool isClear_ = false;
	// 倍率
	float five_ = 5.0f;
	// 半径
	float radius_ = 5.0f;

public: // アクセッサ
	//半径を返す
	float GetRadius() { return radius_; }
	bool GetIsClear() { return isClear_; }
};

