#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "Option.h"
#include "PlayerBullet.h"
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

	//更新
	void Update(ViewProjection& viewprojection);

	//プレイヤーの移動処理
	void Move();

	//プレイヤーの旋回処理
	void Rotate();

	//プレイヤーの攻撃処理
	void Attack();

	//移動処理制限
	void MoveLimit();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//描画
	void Draw(ViewProjection& viewProjection);

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

  private:
	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	//オプション
	Option* option_ = nullptr;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Model* modelOption_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//インプット
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
	//死亡フラグとライフ
	bool isDead_ = false;
	int life_ = 5;

  public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
	Option* GetOption() const { return option_; }
};
