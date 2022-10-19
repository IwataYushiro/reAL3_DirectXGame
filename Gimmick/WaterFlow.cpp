#include "WaterFrow.h"

WaterFlow::WaterFlow() {}

WaterFlow::~WaterFlow() { delete model_; }

//水流初期化
void WaterFlow::Initialize() {

	//水流のモデル
	model_ = Model::CreateFromOBJ("playerbullet", true);

	width_ = 10.0f;  //横幅
	height_ = 20.0f; //縦幅
	speed_ = 0.5f;   //速度

	//ワールド座標初期化
	worldTransform_.Initialize();

	bright_ = 255;     //明るさ
	isActive_ = false; //生きてるか
}

void WaterFlow::Update() {
	//乱数シード生成
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//水流座標の範囲
	std::uniform_real_distribution<float> waterFlowDistX(-30.0f, -10.0f);

	if (isActive_ == false) {

		isActive_ = true;
		worldTransform_.translation_ = {waterFlowDistX(engine), -20.0f, 0.0f};
	}

	if (isActive_ == true) {
		worldTransform_.translation_.y += speed_;
	}
	if (--deathTimer_ <= 0) {
		isActive_ = false;
	}
}

void WaterFlow::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
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

void WaterFlow::OnCollision(){};