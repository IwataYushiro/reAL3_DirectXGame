#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

//水流

class WaterFlow {
  public:
	~WaterFlow();

	//水流初期化
	void Initialize(const Vector3& position, const Vector3& velocity);
	//リセット
	void Reset();

	//水流更新
	void Update();

	//水流描画
	void Draw(ViewProjection& viewProjection);
	//水流のワールド座標を取得
	Vector3 GetWorldPosition();

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャ
	uint32_t texWaterFlow_ = 0;
	//モデルデータ
	Model* model_ = nullptr; //水流

	float width_;  //横幅
	float height_; //縦幅
	// float waterFlowRadius;						//半径
	Vector3 speed_; //速度
	int bright_;    //明るさ

	//寿命
	static const int32_t kLifeTime = 60 * 3;
	//死亡時間
	int32_t deathTimer_ = kLifeTime;

	bool isActive_ = false; //生きてるか

  public:
	//アクセッサ
	//水流
	void OnCollision();
	bool IsActive() const { return isActive_; }
};
