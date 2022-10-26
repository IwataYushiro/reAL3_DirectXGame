#include "WaterFrow.h"

WaterFlow::~WaterFlow() {
	delete model_; 
}

//水流初期化
void WaterFlow::Initialize(const Vector3& position, const Vector3& position2, const Vector3& velocity) {

	audio_ = Audio::GetInstance();
	//サウンドデータ読み込み
	waterFlowSe_ = audio_->LoadWave("sound/se/bubble.wav");
	//テクスチャ読み込み
	texWaterFlow_ = TextureManager::Load("texture/bubble.png");
	//水流のモデル
	model_ = Model::Create();

	width_ = 10.0f;  //横幅
	height_ = 20.0f; //縦幅

	//ワールド座標初期化
	worldTransform_.Initialize();
	//引数の初期座標をセット
	worldTransform_.translation_ = position2;
	worldTransform_.translation_ += position;
	speed_ = velocity;

	bright_ = 255; //明るさ
}
void WaterFlow::Reset() { isActive_ = false; }

void WaterFlow::Update() {

	worldTransform_.translation_ += speed_;

	if (--deathTimer_ <= 0) {
		isActive_ = false;
	}

	//行列更新
	worldTransform_.Update(worldTransform_);
}

void WaterFlow::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, texWaterFlow_);
}

Vector3 WaterFlow::GetWorldPosition() {
	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void WaterFlow::OnCollision() {
	if (!audio_->IsPlaying(waterFlowSe_)) {
	
		audio_->PlayWave(waterFlowSe_, false, 0.1f);
	}
};