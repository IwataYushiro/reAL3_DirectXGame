#include "Option.h"
#include "Player.h"

//初期化
void Option::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture/option.png");

	//ワールド変換の初期化
	worldTransform_.Initialize();

}

//更新
void Option::Update() {	

	worldTransform_.translation_ = {player_->GetWorldPosition().x + 2.0f, player_->GetWorldPosition().y + 2.0f, 0.0f};
}

//描画
void Option::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
//オプションの移動処理
void Option::Move() {

}

//オプションの旋回処理
void Option::Rotate() {

}
