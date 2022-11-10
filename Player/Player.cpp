#include "Player.h"

Player::Player() {}

Player::~Player() {
	delete gimmick_;
	//オプションの解放
	delete modelDead_;
}

void Player::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);
	audio_ = Audio::GetInstance();
	//引数として受け取ったデータをメンバ変数に記録する

	model_ = model;
	modelDead_ = Model::CreateFromOBJ("playerdead", true);

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//音
	jumpSound_ = audio_->LoadWave("sound/se/jump.wav");
	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f, -10.0f, 0.0f };

	prePosition_ = worldTransform_.translation_;

	//挙動初期化
	gimmick_ = new Gimmick();

	isJump = false;
	isSwim = true;
	gravity = -0.6f;
}

void Player::Reset() {
	worldTransform_.translation_ = { 0.0f, -10.0f, 0.0f };
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();

	life_ = 5;
	isDead_ = false;
}
//ゲームオーバー座標
void Player::Death() {}

void Player::Update(ViewProjection& viewprojection) {

	if (!isDead_) {
		Move();
		//ジャンプ処理
		Jump();
		// 水中処理
		Swim();
		//移動制限
		MoveLimit();
	}

	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	if (!isDead_) {
		model_->Draw(worldTransform_, viewProjection);
	}
}

void Player::DrawDead(ViewProjection& viewProjection) {
	modelDead_->Draw(worldTransform_, viewProjection);
}

void Player::Move()
{
	
}

void Player::Jump() {
	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->PlayWave(jumpSound_);
		isJump = true;
		//重力が0になる
		gravity = 0.0f;
	}

	// ジャンプ後重力が浮力を超えたら泳いでる状態にする
	if (isJump == true && gravity <= buoyancy) {
		isSwim = true;
		isJump = false;
	}
}

void Player::Swim() {
	//泳いでいる間
	if (isSwim == true || isJump == true) {
		//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
		worldTransform_.translation_.y -= buoyancy - gravity;
	}

	//重力は徐々に上がる
	gravity -= 0.02f;
	// 重力制限
	if (gravity <= -1.0f) {
		gravity = -1.0f;
	}
}

void Player::MoveLimit() {
	//移動限界座標
	const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 18.0f;
	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	// worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// 画面外に出たら死亡する
	if (worldTransform_.translation_.y <= -30.0f) {
		isDead_ = true;
	}

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
void Player::OnCollisionSpring() {
	isJump = true;
	//重力が0になる
	gravity = 0.5f;
}

void Player::OnCollisionWaterFlow() {
	Vector3 speed;
	speed = { 0.0f, -0.1f, 0.0f };
	isSwim = true;
	worldTransform_.translation_ += speed;
	gravity = -0.2f;
}

void Player::OnCollisionBlock() {
	if (!isJump) {
		worldTransform_.translation_ = prePosition_;
	}
	isSwim = false;
	prePosition_ = worldTransform_.translation_;
}

void Player::OnCollisionStep() {
	worldTransform_.translation_.y += 0.050f;
	isSwim = false;
	prePosition_ = worldTransform_.translation_;
}

void Player::OnCollisionWall() {
	isDead_ = true;
}

void Player::OffCollisionBlock() {
	if (!isSwim && !isJump) {
		isSwim = true;
		gravity = -0.6f;
	}
	prePosition_ = worldTransform_.translation_;
}