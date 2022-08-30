#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//自キャラの弾
class PlayerBullet {
  public:
	PlayerBullet();
	~PlayerBullet();

	//初期化
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	//リセット処理
	void Reset();

	//更新
	void Update();

	//描画
	void Draw(const ViewProjection& viewProjection);

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;
	//寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	//死亡時間
	int32_t deathTimer_ = kLifeTime;
	//死亡フラグ
	bool isDead_ = false;

  public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
};
