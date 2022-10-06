#include "Skydome.h"

Skydome::~Skydome() { delete railcamera_; }
//初期化
void Skydome::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する

	model_ = model;
	railcamera_ = new RailCamera();
	
	//ワールド変換の初期化
	worldTransform_.Initialize();

	railcamera_->Initialize(worldTransform_);
}
//リセット
void Skydome::Reset() { railcamera_->Reset(); }
//更新
void Skydome::Update() { railcamera_->Update(); }

//描画
void Skydome::Draw(ViewProjection& viewprojection) {

	// 3Dモデル描画
	model_->Draw(worldTransform_, viewprojection);
}
