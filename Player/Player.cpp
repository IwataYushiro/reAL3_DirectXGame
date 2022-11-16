#include "Player.h"

Player::~Player() {
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
}

void Player::Reset() {
	worldTransform_.translation_ = { 0.0f, -10.0f, 0.0f };
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();

	isDead_ = false;
}
//ゲームオーバー座標
void Player::Death() {}

void Player::Update(ViewProjection& viewprojection) {

	if (!isDead_) {
		Move();
	}

	worldTransform_.TransferMatrix();

	debugText_->SetPos(50, 25);
	debugText_->Printf("mousePos_(%d,%d)", po.x, po.y);
	debugText_->SetPos(50, 50);
	debugText_->Printf("mouseClick_(%d)", mouseClick_);
}

void Player::Draw(ViewProjection& viewProjection) {
	if (!isDead_) {
		model_->Draw(worldTransform_, viewProjection);
	}
}

void Player::Move()
{
	//マウスの現在の座標を取得する
	GetCursorPos(&po);

	// 左クリックを押したときフラグに1を足す
	if (input_->IsTriggerMouse(0) && mouseClick_ == false)
	{
		mouseClick_ = true;
	}
	else if(input_->IsTriggerMouse(0)) 
	{
		mouseClick_ = false;
	}

	if (mouseClick_ == true)
	{

	}
	else 
	{

	}
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