#include "Option.h"
#include "Player.h"

//初期化
void Option::Initialize(Model* model, const Vector3& position) {
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
	
}

//更新
void Option::Update() {	

	//死亡フラグの立った弾を削除
	optionBullets_.remove_if([](std::unique_ptr<OptionBullet>& bullet) { return bullet->IsDead(); });

	//移動
	Move();
	//回転
	Rotate();  
	//攻撃
	Attack();
	//弾更新
	for (std::unique_ptr<OptionBullet>& bullet : optionBullets_) {
		bullet->Update();
	}

	//行列更新
	worldTransform_.Update(worldTransform_);
}

//描画
void Option::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//弾描画
	for (std::unique_ptr<OptionBullet>& bullet : optionBullets_) {
		bullet->Draw(viewProjection);
	}
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

	Vector3 angle = MyMathUtility::MySetVector3Zero();
	float angleSpeed = 0.1f;

	if (input_->PushKey(DIK_A)) {
		angle.y -= angleSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		angle.y += angleSpeed;
	}

	worldTransform_.rotation_ += angle;
}

//オプションの攻撃処理
void Option::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0.0f, 0.0f, kBulletSpeed);

		velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
		//オプションの座標をコピー
		Vector3 position = worldTransform_.translation_;

		//弾を生成し初期化
		std::unique_ptr<OptionBullet> newBullet = std::make_unique<OptionBullet>();
		newBullet->Initialize(model_, position, velocity);

		//弾を登録
		optionBullets_.push_back(std::move(newBullet));
		//あるメモリの所有権を持つunique_ptrはただ一つしか存在できない
		//その所有権を謙渡するための機能が std::move()
	}
}