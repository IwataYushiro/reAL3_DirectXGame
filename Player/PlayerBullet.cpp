#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {}

PlayerBullet::~PlayerBullet() {}

//初期化
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("texture/playerbullet.png");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

//更新
void PlayerBullet::Update() {
	//座標を移動させる
	worldTransform_.translation_ += velocity_;
	//行列更新
	worldTransform_.PlayerUpdate(worldTransform_);

	//時間経過で死亡
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

//描画
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}