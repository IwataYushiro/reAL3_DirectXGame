#pragma once
#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "GlobalScene.h"
#include <cassert>
#include <list>
#include <memory>

class Player {
public:
	// 構造体
	struct PieceData {
		WorldTransform worldTransform_;
		int type_;
	};

public:
	//初期化
  void Initialize(Model* model, Vector3 pos = {0.0f, 0.0f, 0.0f});

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection);

	//リセット処理
	void Reset();

private:
	//プレイヤーの移動処理
	void Move();

private:
	//インプット
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//音
	Audio* audio_ = nullptr;
	//サウンドデータ
	uint32_t jumpSound_ = 0;

	// ワールド変換データ
	PieceData wt;
	// コスト
	int cost_ = 5;

	//死亡フラグ
	bool isDead_ = false;
	//マウス
	bool mouseClick_;

public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
	int GetCost() { return cost_; }
};
