#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "Gimmick.h"
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
	Player();
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
	//ジャンプ処理
	void Jump();
	// 泳ぐ(水中)
	void Swim();
	//移動処理制限
	void MoveLimit();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//描画
	void Draw(ViewProjection& viewProjection);
	void DrawDead(ViewProjection& viewProjection);

	//衝突を検出したら呼び出されるコールバック関数
	//バネと衝突
	void OnCollisionSpring();
	//水流と衝突
	void OnCollisionWaterFlow();
	// ステージとの当たり判定
	void OnCollisionBlock();
	void OnCollisionStep();
	void OnCollisionWall();
	void OffCollisionBlock();

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
	//死亡フラグとライフ
	bool isDead_ = false;
	int life_ = 5;
	//泳いだか
	bool isSwim;
	// ジャンプしているか
	bool isJump;
	//浮力(変わらない)
	const float buoyancy = -0.5f;
	//重力
	float gravity;
	// 1フレーム前の自機の位置
	Vector3 prePosition_;
	// マウスの座標
	POINT po;
	// クリックフラグ
	bool mouseClick_;

	//仕掛け
	Gimmick* gimmick_ = nullptr;
  public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
};
