#include "EnemyBullet.h"

//初期化
void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("texture/enemybullet.png");

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

//更新
void EnemyBullet::Update() {
	//座標移動
	worldTransform_.translation_ += velocity_;
	//ワールド行列更新
	worldTransform_.Update(worldTransform_);

	//時間経過で死亡
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

//描画
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//モデル描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}