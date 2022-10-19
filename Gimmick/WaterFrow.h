#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

//水流

class WaterFlow {
  public:
	WaterFlow();
	~WaterFlow();

	//水流初期化
	void Initialize();

	//水流更新
	void Update();

	//水流描画
	void Draw(ViewProjection& viewProjection);
	//水流のワールド座標を取得
	Vector3 GetWorldPosition();

  private:
	
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデルデータ
	Model* model_ = nullptr; //水流

	float width_;  //横幅
	float height_; //縦幅
	// float waterFlowRadius;						//半径
	float speed_;                               //速度
	int bright_;    //明るさ

	//寿命
	static const int32_t kLifeTime = 60 * 3;
	//死亡時間
	int32_t deathTimer_ = kLifeTime;

	bool isActive_; //生きてるか

	//水流
	void OnCollision();
	float GetSpeed() { return speed_; }
};

