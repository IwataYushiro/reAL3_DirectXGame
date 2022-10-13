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

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	modelDead_ = Model::CreateFromOBJ("playerdead", true);

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, -10.0f, 0.0f};
	//挙動初期化
	gimmick_ = new Gimmick();

	isSwim = true;
	gravity = -0.6f;
}

void Player::Reset() {
	worldTransform_.translation_ = {0.0f, -10.0f, 0.0f};
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();

	life_ = 5;
	isDead_ = false;
}
//ゲームオーバー座標
void Player::Death() {}

void Player::Update(ViewProjection& viewprojection) {

	if (!isDead_) {

		//移動処理
		Move();
		//ジャンプ処理
		Jump();
		//移動制限
		MoveLimit();
	}

	worldTransform_.TransferMatrix();
	debugText_->SetScale(1.0f);
	debugText_->SetPos(50, 50);
	debugText_->Printf("life:(%d)", life_);
}

void Player::Draw(ViewProjection& viewProjection) {
	if (!isDead_) {
		model_->Draw(worldTransform_, viewProjection);
	}
}

void Player::DrawDead(ViewProjection& viewProjection) {
	modelDead_->Draw(worldTransform_, viewProjection);
}
//移動処理
void Player::Move() {

	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 0.3f;

	//キーボード入力による移動処理
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();
	if (input_->PushKey(DIK_LEFT)) {
		move.x = -moveSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x = moveSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y = moveSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y = -moveSpeed;
	}

	worldTransform_.translation_ += move;
}

void Player::Jump() {
	//スペースキーを押した瞬間泳ぐ(床から離れている状態)
	if (input_->TriggerKey(DIK_SPACE)) {
		isSwim = true;
		//重力が0になる
		gravity = 0.0f;
	}
	//泳いでいる間
	if (isSwim == true) {
		//プレイヤーの座標 -= 浮力(固定) - 重力(徐々に上がる)　
		worldTransform_.translation_.y -= buoyancy - gravity;
		//重力は徐々に上がる
		gravity -= 0.02f;
	}
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
void Player::OnCollisionSpring() {
	isSwim = true;
	//重力が0になる
	gravity = 0.5f;
}
void Player::OnCollisionWaterFlow() {
	isSwim = true;
	worldTransform_.translation_.y += gimmick_->GetWaterFlowSpeed();
	gravity = 0.2f;
}