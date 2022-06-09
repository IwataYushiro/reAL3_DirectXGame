#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

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
	
	
	//乱数シード生成器
	std::random_device seed_gen;
	// メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	// 乱数範囲を指定(回転角)
	std::uniform_real_distribution<float> scaleDistX(1.0f,3.0f);
	std::uniform_real_distribution<float> scaleDistY(1.0f,3.0f);
	std::uniform_real_distribution<float> scaleDistZ(1.0f,3.0f);
	// 乱数範囲を指定(回転角)
	std::uniform_real_distribution<float> rotationDistX(0.0f, MyMathUtility::PI);
	std::uniform_real_distribution<float> rotationDistY(0.0f, MyMathUtility::PI);
	std::uniform_real_distribution<float> rotationDistZ(0.0f, MyMathUtility::PI);
	// 乱数範囲を指定(座標)
	std::uniform_real_distribution<float> translationDistX(-10.0f, 10.0f);
	std::uniform_real_distribution<float> translationDistY(-10.0f, 10.0f);
	std::uniform_real_distribution<float> translationDistZ(-10.0f, 10.0f);
	
	// X,Y,Z軸周りのスケーリングを設定
	for (WorldTransform& worldTransform : worldTransforms_)
	{
		//ワールドトランスフォームの初期化
		worldTransform.Initialize();

		//乱数エンジンを渡し、指定範囲からランダムな数値を得る(拡大)
		float scaleValueX = scaleDistX(engine);
		float scaleValueY = scaleDistY(engine);
		float scaleValueZ = scaleDistZ(engine);
		//乱数エンジンを渡し、指定範囲からランダムな数値を得る(回転角)
		float rotationValueX = rotationDistX(engine);
		float rotationValueY = rotationDistY(engine);
		float rotationValueZ = rotationDistZ(engine);
		//乱数エンジンを渡し、指定範囲からランダムな数値を得る(座標)
		float translationValueX = translationDistX(engine);
		float translationValueY = translationDistY(engine);
		float translationValueZ = translationDistZ(engine);

		worldTransform.scale_ = {scaleValueX, scaleValueY, scaleValueZ};
		// X,Y,Z軸周りの回転角を設定
		worldTransform.rotation_ = {rotationValueX, rotationValueY, rotationValueZ};
		// X,Y,Z軸周りの平行移動を設定
		worldTransform.translation_ = {translationValueX, translationValueY, translationValueZ};
		
		//変換
		worldTransform.matWorld_ = MyMathUtility::MyMatrix4WorldTransform(worldTransform);

		//行列の転送
		worldTransform.TransferMatrix();
	}
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
	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, debugCamera_->GetViewProjection(), textureHandle_);
	}
	//ライン描画が参照するビュープロジェクションを指定する(アドレス無し)

	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeVertex_[edgeList_[i][0]], cubeVertex_[edgeList_[i][1]], color_);
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
