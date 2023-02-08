#pragma once
#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "GlobalScene.h"
#include <memory>

class Player {
public:
	//初期化
  void Initialize(Model* model, Vector3 pos = {0.0f, 0.0f, 0.0f});

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection);

	//リセット処理
	void Reset();

	// 当たり判定
	void OnCollisionStage(bool collisionFlag);
	void OnCollisionPlayer(bool collisionFlag);

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
	WorldTransform worldTransform_;
	// 前フレーム座標
	Vector3 prePos_{};
	// 半径
	float radius_ = 1.5f;
	//死亡フラグ
	bool isDead_ = false;

public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
	Vector3 GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }

};
