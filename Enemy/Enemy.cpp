#include "Enemy.h"


Enemy::Enemy() {}

Enemy::~Enemy() {}

// 初期化
  void Enemy::Initialize(Model* model,const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("texture/enemy.png");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = {15.0f, 15.0f, 0.0f};
	velocity_ = velocity;
}

//更新
void Enemy::Update() {
	//座標を移動させる
	worldTransform_.translation_ -= velocity_;
	//行列更新
	worldTransform_.PlayerUpdate(worldTransform_);

}

//描画
void Enemy::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}