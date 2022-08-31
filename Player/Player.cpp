#include "Player.h"

Player::Player() {}

Player::~Player() {
	//オプションの解放
	delete option_;
	delete modelBullet_;
	delete modelOption_;
}

void Player::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	modelBullet_ = Model::CreateFromOBJ("playerbullet", true);
	modelOption_ = Model::CreateFromOBJ("option", true);
	//オプションの生成
	option_ = new Option();

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();
	//ここでオプション初期化
	option_->Initialize(modelOption_, worldTransform_.translation_);
}

void Player::Reset() {
	worldTransform_.translation_ = MyMathUtility::MySetVector3Zero();
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();

	life_ = 5;
	isDead_ = false;
	option_->Reset(worldTransform_.translation_);
	//弾リセット
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Reset();
	}
}

void Player::Update(ViewProjection& viewprojection) {

	if (!isDead_) {
		//死亡フラグの立った弾を削除
		bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

		//移動処理
		Move();
		//旋回処理
		Rotate();
		//攻撃処理
		Attack();

		//オプションの更新処理
		option_->Update(viewprojection);
		//弾更新
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Update();
		}

		//移動制限
		MoveLimit();

		worldTransform_.TransferMatrix();
	}
	debugText_->SetScale(1.0f);
	debugText_->SetPos(50, 50);
	debugText_->Printf("life:(%d)", life_);
}

void Player::Draw(ViewProjection& viewProjection) {
	if (!isDead_) {
		model_->Draw(worldTransform_, viewProjection);

		//弾描画
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Draw(viewProjection);
		}

		//オプション描画
		option_->Draw(viewProjection);
	}
}

//移動処理
void Player::Move() {

	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 0.3f;

	//キーボード入力による移動処理
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();
	if (input_->PushKey(DIK_A)) {
		move.x = -moveSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x = moveSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.y = moveSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y = -moveSpeed;
	}

	worldTransform_.translation_ += move;
}

//旋回処理
void Player::Rotate() {

	Vector3 angle = MyMathUtility::MySetVector3Zero();
	float angleSpeed = 0.1f;

	if (input_->PushKey(DIK_Q)) {
		angle.y -= angleSpeed;
	}
	if (input_->PushKey(DIK_E)) {
		angle.y += angleSpeed;
	}

	worldTransform_.rotation_ += angle;
}

//攻撃処理
void Player::Attack() {

	if (input_->IsTriggerMouse(0)) {
		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
		//自キャラの座標をコピー
		Vector3 position = worldTransform_.translation_;

		//弾を生成し初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelBullet_, position, velocity);

		//弾を登録
		bullets_.push_back(std::move(newBullet));
		//あるメモリの所有権を持つunique_ptrはただ一つしか存在できない
		//その所有権を謙渡するための機能が std::move()
	}
}

void Player::MoveLimit() {
	//移動限界座標
	const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 18.0f;
	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	//行列更新
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
}

//ワールド座標を取得
Vector3 Player::GetWorldPosition() {

	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

//衝突を検出したら呼び出されるコールバック関数
void Player::OnCollision() {
	life_--;
	if (life_ <= 0) {
		isDead_ = true;
	}
}