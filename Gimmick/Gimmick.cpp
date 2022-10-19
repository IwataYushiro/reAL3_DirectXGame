#include "Gimmick.h"
#include "Player.h"

Gimmick::Gimmick() {}

Gimmick::~Gimmick() {
	delete modelSpring_;
	
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



Vector3 Gimmick::GetWorldPositionSpring() {
	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransformSpring_.translation_.x;
	worldPos.y = worldTransformSpring_.translation_.y;
	worldPos.z = worldTransformSpring_.translation_.z;

	return worldPos;
}


void Gimmick::OnCollisionSpring(){};
