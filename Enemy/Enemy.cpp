#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

// 初期化
void Enemy::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("texture/enemy.png");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = {1.0f, 1.0f, 30.0f};
}

//更新
void Enemy::Update() {
	//座標を移動させる
	switch (phase_) {
	case Enemy::Phase::Approach:

		UpdateApproach();
		break;

	case Enemy::Phase::Leave:
		UpdateLeave();
		break;
	}

	//行列更新
	worldTransform_.Update(worldTransform_);
}

//描画
void Enemy::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//状態変化用の更新関数
//接近
void Enemy::UpdateApproach() {
	//速度
	Vector3 velocity_;

	//移動
	velocity_ = {0.0f, 0.0f, -0.1f};
	worldTransform_.translation_ += velocity_;

	//指定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

//離脱
void Enemy::UpdateLeave() {
	//速度
	Vector3 velocity_;

	//移動
	velocity_ = {0.1f, 0.1f, 0.0f};
	worldTransform_.translation_ += velocity_;
}