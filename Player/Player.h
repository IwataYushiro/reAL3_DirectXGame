#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

class Player {
  public:
	~Player();

	//初期化
	void Initialize(Model* model);
	//リセット処理
	void Reset();
	//死んだら
	void Death();
	//更新
	void Update(ViewProjection& viewprojection);

	//プレイヤーの移動処理
	void Move();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//描画
	void Draw(ViewProjection& viewProjection);

  private:
	//音
	Audio* audio_ = nullptr;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Model* modelDead_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//インプット
	Input* input_ = nullptr;
	//サウンドデータ
	uint32_t jumpSound_ = 0;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
	//死亡フラグ
	bool isDead_ = false;
	int life_ = 5;
	//マウス
	bool mouseClick_;
	//座標
	POINT po;

  public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
};
