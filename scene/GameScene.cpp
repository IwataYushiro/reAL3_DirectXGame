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
		cubeRotatedVertexX[i] = cubeBaseVertex[i];
		cubeRotatedVertexY[i] = cubeBaseVertex[i];
		cubeRotatedVertexZ[i] = cubeBaseVertex[i];
		cubeScaledVertex[i] = cubeBaseVertex[i];
	}
	// 3Dモデルの生成
	model_ = Model::Create();
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

	//平行移動
	for (int i = 0; i < 8; i++) {
		cubeMoveVertex[i].x =
		  affinMove[0].x * cubeBaseVertex[i].x + affinMove[0].y * cubeBaseVertex[i].y +
		  affinMove[0].z * cubeBaseVertex[i].z + affinMove[0].w;

		cubeMoveVertex[i].y =
		  affinMove[1].x * cubeBaseVertex[i].x + affinMove[1].y * cubeBaseVertex[i].y +
		  affinMove[1].z * cubeBaseVertex[i].z + affinMove[1].w;

		cubeMoveVertex[i].z =
		  affinMove[2].x * cubeBaseVertex[i].x + affinMove[2].y * cubeBaseVertex[i].y +
		  affinMove[2].z * cubeBaseVertex[i].z + affinMove[2].w;

	}
	//X軸回転
	for (int i = 0; i < 8; i++) {
		cubeRotatedVertexX[i].x = affinRotatedX[0].x * cubeBaseVertex[i].x +
		                      affinRotatedX[0].y * cubeBaseVertex[i].y +
		                      affinRotatedX[0].z * cubeBaseVertex[i].z + affinRotatedX[0].w;

		cubeRotatedVertexX[i].y = affinRotatedX[1].x * cubeBaseVertex[i].x +
		                      affinRotatedX[1].y * cubeBaseVertex[i].y +
		                      affinRotatedX[1].z * cubeBaseVertex[i].z + affinRotatedX[1].w;

		cubeRotatedVertexX[i].z = affinRotatedX[2].x * cubeBaseVertex[i].x +
		                      affinRotatedX[2].y * cubeBaseVertex[i].y +
		                      affinRotatedX[2].z * cubeBaseVertex[i].z + affinRotatedX[2].w;
	}
	// Y軸回転
	for (int i = 0; i < 8; i++) {
		cubeRotatedVertexY[i].x = affinRotatedY[0].x * cubeBaseVertex[i].x +
		                          affinRotatedY[0].y * cubeBaseVertex[i].y +
		                          affinRotatedY[0].z * cubeBaseVertex[i].z + affinRotatedY[0].w;

		cubeRotatedVertexY[i].y = affinRotatedY[1].x * cubeBaseVertex[i].x +
		                          affinRotatedY[1].y * cubeBaseVertex[i].y +
		                          affinRotatedY[1].z * cubeBaseVertex[i].z + affinRotatedY[1].w;

		cubeRotatedVertexY[i].z = affinRotatedY[2].x * cubeBaseVertex[i].x +
		                          affinRotatedY[2].y * cubeBaseVertex[i].y +
		                          affinRotatedY[2].z * cubeBaseVertex[i].z + affinRotatedY[2].w;
	}
	// Z軸回転
	for (int i = 0; i < 8; i++) {
		cubeRotatedVertexZ[i].x = affinRotatedZ[0].x * cubeBaseVertex[i].x +
		                          affinRotatedZ[0].y * cubeBaseVertex[i].y +
		                          affinRotatedZ[0].z * cubeBaseVertex[i].z + affinRotatedZ[0].w;

		cubeRotatedVertexZ[i].y = affinRotatedZ[1].x * cubeBaseVertex[i].x +
		                          affinRotatedZ[1].y * cubeBaseVertex[i].y +
		                          affinRotatedZ[1].z * cubeBaseVertex[i].z + affinRotatedZ[1].w;

		cubeRotatedVertexZ[i].z = affinRotatedZ[2].x * cubeBaseVertex[i].x +
		                          affinRotatedZ[2].y * cubeBaseVertex[i].y +
		                          affinRotatedZ[2].z * cubeBaseVertex[i].z + affinRotatedZ[2].w;
	}
	//拡大
	for (int i = 0; i < 8; i++) {
		cubeScaledVertex[i].x = affinScaled[0].x * cubeBaseVertex[i].x +
		                      affinScaled[0].y * cubeBaseVertex[i].y +
		                      affinScaled[0].z * cubeBaseVertex[i].z + affinScaled[0].w;

		cubeScaledVertex[i].y = affinScaled[1].x * cubeBaseVertex[i].x +
		                      affinScaled[1].y * cubeBaseVertex[i].y +
		                      affinScaled[1].z * cubeBaseVertex[i].z + affinScaled[1].w;

		cubeScaledVertex[i].z = affinScaled[2].x * cubeBaseVertex[i].x +
		                      affinScaled[2].y * cubeBaseVertex[i].y +
		                      affinScaled[2].z * cubeBaseVertex[i].z + affinScaled[2].w;
	}
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
	//X軸回転
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeRotatedVertexX[baseEdgeList[i][0]], cubeRotatedVertexX[baseEdgeList[i][1]], rotatedColorX);
	}
	// Y軸回転
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeRotatedVertexY[baseEdgeList[i][0]], cubeRotatedVertexY[baseEdgeList[i][1]],
		  rotatedColorY);
	}
	// Z軸回転
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		  cubeRotatedVertexZ[baseEdgeList[i][0]], cubeRotatedVertexZ[baseEdgeList[i][1]],
		  rotatedColorZ);
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
