#include "EnemyBullet.h"

//初期化
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
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
void EnemyBullet::Reset() { isDead_ = true; }
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

//衝突を検出したら呼び出されるコールバック関数
void EnemyBullet::OnCollision() { isDead_ = true; }

//ワールド座標を取得
Vector3 EnemyBullet::GetWorldPosition() {

	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}