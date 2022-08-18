#pragma once
#include "EnemyBullet.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

//敵
class Enemy {
  public:
	  //弾発射間隔
	static const int kFireInterval = 60;
	//初期化
	void Initialize(Model* model);
	//接近フェーズ初期化
	void InitializeApproach();
	//更新
	void Update();
	//弾発射
	void Fire();

	//描画
	void Draw(const ViewProjection& viewProjection);

	//状態変化用の更新関数
	//接近
	void UpdateApproach();
	//離脱
	void UpdateLeave();

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//弾
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//行動フェーズ
	enum class Phase {
		Approach, //接近
		Leave,    //離脱
	};

	//フェーズ
	Phase phase_;
	//弾発射タイマー
	int32_t fireTimer = 0;
};
