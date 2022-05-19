#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("02-01/mario.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//スケーリング行列を宣言
	Matrix4 matScale;
	matScale = MathUtility::Matrix4Scaling(
	  worldTransform_.scale_.x, worldTransform_.scale_.y, worldTransform_.scale_.z);
	//単位行列を代入
	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransform_.matWorld_.operator*=(matScale);
	//行列の転送
	worldTransform_.TransferMatrix();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1260, 720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス無し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	//ライン描画が参照するビュープロジェクションを指定する(アドレス無し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	//デバッグカメラの更新
	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 3Dモデル描画
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	//ライン描画が参照するビュープロジェクションを指定する(アドレス無し)

	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeVertex[edgeList[i][0]], cubeVertex[edgeList[i][1]], color);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
