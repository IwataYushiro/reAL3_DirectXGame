#include "Player.h"

void Player::Initialize(Model* model, Vector3 pos) {
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
	wt.worldTransform_.Initialize();
	wt.worldTransform_.translation_ = pos;
  
}

void Player::Update() {
	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 1.0f;

	// キーボード入力による移動処理
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();
	if (input_->PushKey(DIK_A)) {
		move.x = -moveSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x = moveSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.z = moveSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.z = -moveSpeed;
	}

	wt.worldTransform_.translation_ += move;
	wt.worldTransform_.Update(wt.worldTransform_);
}

void Player::Draw(ViewProjection& viewProjection) { 
	model_->Draw(wt.worldTransform_, viewProjection);
}

void Player::Reset() {

}

void Player::Move() {

}