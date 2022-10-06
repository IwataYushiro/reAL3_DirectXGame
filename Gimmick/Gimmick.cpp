#include "Gimmick.h"
#include "Player.h"

Gimmick::Gimmick() {}

Gimmick::~Gimmick() { delete modelSpring_; }

//初期化
void Gimmick::Initialize() {
	//バネ初期化
	InitializeSpring();
}

void Gimmick::InitializeSpring() { 
	//バネのモデル
	modelSpring_ = Model::Create(); 
	
	worldTransformSpring_.Initialize();
	worldTransformSpring_.translation_ = {25.0f, -15.0f, 0.0f};
}

//更新
void Gimmick::Update() { 


	//ワールド行列更新
	worldTransformSpring_.Update(worldTransformSpring_); 
}

//描画
void Gimmick::Draw(ViewProjection& viewProjection) {
	//バネ
	DrawSpring(viewProjection);
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