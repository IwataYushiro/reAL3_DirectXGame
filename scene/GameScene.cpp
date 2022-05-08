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
	//平行移動、回転、拡大の行列の初期化
	for (int i = 0; i < 8; i++) {
		cubeMoveVertex[i] = cubeBaseVertex[i];
		cubeRotatedVertex[i] = cubeBaseVertex[i];
		cubeScaledVertex[i] = cubeBaseVertex[i];
	}

	//平行移動
	for (int i = 0; i < 8; i++) {
		cubeBaseVertex[i].x =
		  (affinScaled[0].x * cubeScaledVertex[i].x + affinScaled[0].y * cubeScaledVertex[i].y +
		   affinScaled[0].z * cubeScaledVertex[i].z + affinScaled[0].w) +
		  (affinRotated[0].x * cubeRotatedVertex[i].x + affinRotated[0].y * cubeRotatedVertex[i].y +
		   affinRotated[0].z * cubeRotatedVertex[i].z + affinRotated[0].w)+
		  (affinMove[0].x * cubeMoveVertex[i].x + affinMove[0].y * cubeMoveVertex[i].y +
		   affinMove[0].z * cubeMoveVertex[i].z + affinMove[0].w);

		cubeBaseVertex[i].y =
		  (affinScaled[1].x * cubeScaledVertex[i].x + affinScaled[1].y * cubeScaledVertex[i].y +
		   affinScaled[1].z * cubeScaledVertex[i].z + affinScaled[1].w) +
		  (affinRotated[1].x * cubeRotatedVertex[i].x + affinRotated[1].y * cubeRotatedVertex[i].y +
		   affinRotated[1].z * cubeRotatedVertex[i].z + affinRotated[1].w) +
		  (affinMove[1].x * cubeMoveVertex[i].x + affinMove[1].y * cubeMoveVertex[i].y +
		   affinMove[1].z * cubeMoveVertex[i].z + affinMove[1].w);

		cubeBaseVertex[i].z =
		  (affinScaled[2].x * cubeScaledVertex[i].x + affinScaled[2].y * cubeScaledVertex[i].y +
		   affinScaled[2].z * cubeScaledVertex[i].z + affinScaled[2].w) +
		  (affinRotated[2].x * cubeRotatedVertex[i].x + affinRotated[2].y * cubeRotatedVertex[i].y +
		   affinRotated[2].z * cubeRotatedVertex[i].z + affinRotated[2].w) +
		  (affinMove[2].x * cubeMoveVertex[i].x + affinMove[2].y * cubeMoveVertex[i].y +
		   affinMove[2].z * cubeMoveVertex[i].z + affinMove[2].w);
	}
	//回転
	

	// 3Dモデルの生成
	model_ = Model::Create();
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
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

	//ライン描画が参照するビュープロジェクションを指定する(アドレス無し)
	//ベース
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeBaseVertex[baseEdgeList[i][0]], cubeBaseVertex[baseEdgeList[i][1]], baseColor);
	}
	//平行移動
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeMoveVertex[baseEdgeList[i][0]], cubeMoveVertex[baseEdgeList[i][1]], moveColor);
	}
	//回転
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeRotatedVertex[baseEdgeList[i][0]], cubeRotatedVertex[baseEdgeList[i][1]],
		  rotatedColor);
	}
	//拡大
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeScaledVertex[baseEdgeList[i][0]], cubeScaledVertex[baseEdgeList[i][1]], scaledColor);
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
