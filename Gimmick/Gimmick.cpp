#include "Gimmick.h"
#include "Player.h"

Gimmick::Gimmick() {}

Gimmick::~Gimmick() {
	delete modelSpring_;
	delete modelWaterFlow_;
}

//初期化
void Gimmick::Initialize() {
	//バネ初期化
	InitializeSpring();
	//水流初期化
	InitializeWaterFlow();
}

void Gimmick::InitializeSpring() {
	//バネのモデル
	modelSpring_ = Model::Create();

	worldTransformSpring_.translation_ = {25.0f, -15.0f, 0.0f};
	worldTransformSpring_.Initialize();
}
//水流初期化
void Gimmick::InitializeWaterFlow() {

	//水流のモデル
	modelWaterFlow_ = Model::CreateFromOBJ("playerbullet", true);

	waterFlowWidth_ = 10.0f;  //横幅
	waterFlowHeight_ = 20.0f; //縦幅
	waterFlowSpeed_ = 0.5f;   //速度
	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		//ワールド座標初期化
		worldTransformWaterFlow_[i].Initialize();

		waterFlowBright_[i] = 255;     //明るさ
		isActiveWaterFlow_[i] = false; //生きてるか
	}
}
//更新
void Gimmick::Update() {
	//水流更新
	UpdateWaterFlow();
	//ワールド行列更新
	worldTransformSpring_.Update(worldTransformSpring_);
	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		worldTransformWaterFlow_[i].Update(worldTransformWaterFlow_[i]);
	}
}
void Gimmick::UpdateWaterFlow() {
	//乱数シード生成
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//水流座標の範囲
	std::uniform_real_distribution<float> waterFlowDistX(-30.0f, -10.0f);

	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		if (isActiveWaterFlow_[i] == false) {

			isActiveWaterFlow_[i] = true;
			worldTransformWaterFlow_[i].translation_ = {waterFlowDistX(engine), -20.0f, 0.0f};

			if (i % 2 == 0) {
				break;
			}
		}
	}

	for (int i = 0; i < WATERFLOW_MAX_; i++) {

		if (isActiveWaterFlow_[i] == true) {
			worldTransformWaterFlow_[i].translation_.y += waterFlowSpeed_;
		}
		if (worldTransformWaterFlow_[i].translation_.y >= 30.0f) {
			isActiveWaterFlow_[i] = false;
		}
	}
	
}
//描画
void Gimmick::Draw(ViewProjection& viewProjection) {
	//バネ
	DrawSpring(viewProjection);
	//水流
	DrawWaterFlow(viewProjection);
}

void Gimmick::DrawSpring(ViewProjection& viewProjection) {

	modelSpring_->Draw(worldTransformSpring_, viewProjection);
}

void Gimmick::DrawWaterFlow(ViewProjection& viewProjection) {
	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		if (isActiveWaterFlow_[i] == true) {
			modelWaterFlow_->Draw(worldTransformWaterFlow_[i], viewProjection);
		}
	}
}

Vector3 Gimmick::GetWorldPositionSpring() {
	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransformSpring_.translation_.x;
	worldPos.y = worldTransformSpring_.translation_.y;
	worldPos.z = worldTransformSpring_.translation_.z;

	return worldPos;
}

Vector3& Gimmick::GetWorldPositionWaterFlow() {
	//ワールド座標を取得
	Vector3 worldPos[WATERFLOW_MAX_];

	for (int i = 0; i < WATERFLOW_MAX_; i++) {

		//ワールド行列の平行移動成分を取得
		worldPos[i].x = worldTransformWaterFlow_[i].translation_.x;
		worldPos[i].y = worldTransformWaterFlow_[i].translation_.y;
		worldPos[i].z = worldTransformWaterFlow_[i].translation_.z;

		return worldPos[i];
	}
}
void Gimmick::OnCollisionSpring(){};
void Gimmick::OnCollisionWaterFlow(){};