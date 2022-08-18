#include "EnemyBullet.h"

//初期化
void EnemyBullet::Initialize(Model* model, const Vector3& position) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("texture/enemybullet.png");

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

//更新
void EnemyBullet::Update() {

	//ワールド行列更新
	worldTransform_.Update(worldTransform_);
}

//描画
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//モデル描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}