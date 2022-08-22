#include "Option.h"
#include "Player.h"

//初期化
void Option::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture/option.png");

	//ワールド変換の初期化
	worldTransform_.Initialize();
	////引数で受け取った初期座標をセット
	worldTransform_.translation_ = {position.x + 4.0f, position.y + 4.0f, 0.0f};
	velocity_ = velocity;
}

//更新
void Option::Update() {	
	//移動
	//座標を移動させる
	worldTransform_.translation_ += velocity_;
	//行列更新
	worldTransform_.Update(worldTransform_);
}

//描画
void Option::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//オプションの移動処理
void Option::Move() {
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

//オプションの旋回処理
void Option::Rotate() {

}
