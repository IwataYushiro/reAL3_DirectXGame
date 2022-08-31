#include "Enemy.h"
#include "Player.h"
// 初期化
Enemy::~Enemy() { delete modelBullet_; }

void Enemy::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	modelBullet_ = Model::CreateFromOBJ("enemybullet", true);
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("texture/enemy.png");

	//シングルトンインスタンスを取得
	debugText_ = DebugText::GetInstance();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//引数で受け取った初期座標をセット
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	worldTransform_.translation_ = {1.0f, 1.0f, 80.0f};

	//初期フェーズ
	phase_ = Phase::Approach;
	//接近フェーズ初期化
	InitializeApproach();
}

// 接近フェーズ初期化
void Enemy::InitializeApproach() {
	//発射タイマー初期化
	fireTimer = kFireInterval;
}

//リセット
void Enemy::Reset() {
	worldTransform_.translation_ = {1.0f, 1.0f, 80.0f};
	//初期フェーズ
	phase_ = Phase::Approach;

	life_ = 15;
	isDead_ = false;
	//弾リセット
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Reset();
	}
}

//更新
void Enemy::Update() {

	if (!isDead_) {
		//死亡フラグの立った弾を削除
		enemyBullets_.remove_if(
		  [](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });

		//座標を移動させる
		switch (phase_) {
		case Enemy::Phase::Approach:

			UpdateApproach();
			break;

		case Enemy::Phase::Attack:

			UpdateAttack();
			break;

		case Enemy::Phase::Leave:
			UpdateLeave();
			break;
		}
		//弾更新
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Update();
		}

		//行列更新
		worldTransform_.Update(worldTransform_);
	}
	debugText_->SetScale(1.0f);
	debugText_->SetPos(50, 100);
	debugText_->Printf("enemy life:(%d)", life_);
}

//弾発射
void Enemy::Fire() {

	assert(player_);

	//弾の速度
	const float kBulletSpeed = -1.0f;
	Vector3 velocity;

	//自機のワールド座標を取得
	player_->GetWorldPosition();
	//敵のワールド座標を取得
	GetWorldPosition();
	//敵→自機の差分ベクトルを求める
	velocity = player_->GetWorldPosition() -= GetWorldPosition();
	// ベクトルの正規化
	MyMathUtility::MyVector3Normalize(velocity);
	// ベクトルの長さを速さに合わせる
	velocity.z = kBulletSpeed;

	////ベクトルと行列で掛け算
	// velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
	////敵キャラの座標をコピー
	// Vector3 position = worldTransform_.translation_;

	//弾を生成し初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(modelBullet_, worldTransform_.translation_, velocity);

	//弾を登録
	enemyBullets_.push_back(std::move(newBullet));
}

//描画
void Enemy::Draw(const ViewProjection& viewProjection) {
	if (!isDead_) {
		//モデルの描画
		model_->Draw(worldTransform_, viewProjection, textureHandle_);

		//弾描画
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(viewProjection);
		}
	}
}

//状態変化用の更新関数
//接近
void Enemy::UpdateApproach() {
	//速度
	Vector3 velocity;

	//移動
	velocity = {0.0f, 0.0f, -0.1f};
	worldTransform_.translation_ += velocity;

	//発射タイマーカウントダウン
	fireTimer--;
	//指定時間に達した
	if (fireTimer <= 0) {
		//弾発射
		Fire();
		//発射タイマー初期化
		fireTimer = kFireInterval;
	}

	//指定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 50.0f) {
		phase_ = Phase::Attack;
	}
}
//攻撃
void Enemy::UpdateAttack() {

	//速度
	Vector3 velocity;

	//移動
	velocity = {0.1f, 0.0f, 0.0f};
	if (isReverse_) {
		worldTransform_.translation_ -= velocity;
	} else {
		worldTransform_.translation_ += velocity;
	}

	//指定の位置に到達したら反転
	if (worldTransform_.translation_.x >= 30.0f) {
		isReverse_ = true;
	}
	if (worldTransform_.translation_.x <= -30.0f) {
		isReverse_ = false;
	}

	//発射タイマーカウントダウン
	fireTimer--;
	//指定時間に達した
	if (fireTimer <= 0) {
		//弾発射
		Fire();
		//発射タイマー初期化
		fireTimer = kFireInterval;
	}
}

//離脱
void Enemy::UpdateLeave() {
	//速度
	Vector3 velocity;

	//移動
	velocity = {0.1f, 0.1f, 0.0f};
	worldTransform_.translation_ += velocity;
}

//ワールド座標を取得
Vector3 Enemy::GetWorldPosition() {

	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
//衝突を検出したら呼び出されるコールバック関数
void Enemy::OnCollisionPlayer() {
	life_ -= 2;
	if (life_ <= 0) {
		isDead_ = true;
	}
}

void Enemy::OnCollisionOption() {
	life_--;
	if (life_ <= 0) {
		isDead_ = true;
	}
}