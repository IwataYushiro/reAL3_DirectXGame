#include "Player.h"

void Player::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	audio_ = Audio::GetInstance();

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//音
	jumpSound_ = audio_->LoadWave("sound/se/jump.wav");
  
}

void Player::Update(const Vector3& pos, int phase) {
}

void Player::Draw(ViewProjection& viewProjection) {
}

void Player::Reset() {

}

void Player::Move() {

}