#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//敵の弾
class EnemyBullet {
  public:
	//初期化
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	//更新
	void Update();
	//描画
	void Draw(const ViewProjection& viewProjection);

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_;

	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//死亡時間
	int32_t deathTimer_ = kLifeTime;
	//死亡フラグ
	bool isDead_ = false;

  public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
};
