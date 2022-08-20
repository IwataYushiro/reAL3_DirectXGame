#include "Skydome.h"

//初期化
void Skydome::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	
	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();
}

//更新
void Skydome::Update() {

}

//描画
void Skydome::Draw(ViewProjection& viewprojection) { 

	//3Dモデル描画
	model_->Draw(worldTransform_, viewprojection); 
}
