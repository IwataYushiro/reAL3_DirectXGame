#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	// BGM解放

	//自キャラの解放
	delete player_;
	delete modelPlayer_;
	//仕掛け解放
	delete gimmick_;
	//天球データ解放
	delete skydome_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// BGMロード

	// 3Dモデルの生成
	model_ = Model::Create();
	//プレイヤー
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	//天球
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	//自キャラの生成
	player_ = new Player();
	//仕掛け生成
	gimmick_ = new Gimmick();
	//天球データ生成
	skydome_ = new Skydome();

	//自キャラの初期化
	player_->Initialize(modelPlayer_);
	//仕掛け初期化
	gimmick_->Initialize();
	//天球データ初期化
	skydome_->Initialize(modelSkydome_);
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	scene_ = title;
	//仕掛けに自機のアドレスを渡す
	gimmick_->SetPlayer(player_);
}

void GameScene::Update() {
	switch (scene_) {
	case title:
		//天球データの更新処理
		skydome_->Update();

		//自キャラの更新処理
		player_->Update(viewProjection_);
		//仕掛け更新
		gimmick_->Update();

		//当たり判定
		ChackAllCollisions();
		break;

	case howtoplay:
		//天球データの更新処理
		skydome_->Update();

		//遊び方説明
		debugText_->Print("WASD move player", 200, 200, 2.0f);
		debugText_->Print("QE rotate player", 200, 250, 2.0f);
		debugText_->Print("MOUSE move option", 200, 300, 2.0f);
		debugText_->Print("MOUSE LEFT shot", 200, 350, 2.0f);

		debugText_->Print(" SPACE game start", 200, 450, 2.0f);

		if (input_->TriggerKey(DIK_SPACE)) {
			player_->Reset();
			scene_ = stage1;
			break;
		}
		break;

	case stage1:
		//天球データの更新処理
		skydome_->Update();
		//自キャラの更新処理
		player_->Update(viewProjection_);

		if (player_->IsDead()) {
			scene_ = gameover;
			break;
		}
		//当たり判定
		ChackAllCollisions();
		break;

	case stage2:
		//天球データの更新処理
		skydome_->Update();
		//自キャラの更新処理
		player_->Update(viewProjection_);

		if (player_->IsDead()) {
			scene_ = gameover;
			break;
		}
		//当たり判定
		ChackAllCollisions();
		break;
	case stage3:
		//天球データの更新処理
		skydome_->Update();
		//自キャラの更新処理
		player_->Update(viewProjection_);

		if (player_->IsDead()) {
			scene_ = gameover;
			break;
		}
		//当たり判定
		ChackAllCollisions();
		break;

	case normalend:
		debugText_->Print(" GAME CLEAR...?", 200, 200, 3.0f);
		debugText_->Print(" SPACE title", 200, 350, 2.0f);

		debugText_->Print(" HINT stage3 enemylife 0", 200, 500, 2.0f);
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = title;
			break;
		}
		break;

	case trueend:
		debugText_->Print(" GAME CLEAR!", 200, 200, 3.0f);
		debugText_->Print(" SPACE title", 200, 350, 2.0f);
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = title;
			break;
		}
		break;

	case gameover:

		debugText_->Print(" GAME OVER", 200, 200, 3.0f);
		debugText_->Print(" SPACE title", 200, 350, 2.0f);
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = title;
			break;
		}
		break;
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
	switch (scene_) {
	case title:
		skydome_->Draw(viewProjection_);
		gimmick_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		break;
	case howtoplay:
		skydome_->Draw(viewProjection_);
		break;
	case stage1:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;
	case stage2:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;
	case stage3:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;

	case normalend:
		break;

	case trueend:
		break;

	case gameover:
		player_->DrawDead(viewProjection_);
		break;
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

//衝突判定と応答
void GameScene::ChackAllCollisions() {

	//判定対象A,Bの座標
	Vector3 posA, posB;
	
	//A,Bの座標の距離用
	Vector3 posAB;
	
	//判定対象A,Bの半径
	float radiusA;
	float radiusB;
	float radiusAB;
	

	//配列用のC
	Vector3 posC;
	Vector3 posAC;
	float radiusC;
	
	//配列用のAC
	float radiusAC;

#pragma region 自機とバネの当たり判定
	//それぞれの半径
	radiusA = 1.0f;
	radiusB = 3.0f;

	//自機の座標
	posA = player_->GetWorldPosition();

	//自機とバネの当たり判定
	posB = gimmick_->GetWorldPositionSpring();
	//座標A,Bの距離を求める
	posAB.x = (posB.x - posA.x) * (posB.x - posA.x);
	posAB.y = (posB.y - posA.y) * (posB.y - posA.y);
	posAB.z = (posB.z - posA.z) * (posB.z - posA.z);
	radiusAB = (radiusA + radiusB) * (radiusA + radiusB);

	//球と球の交差判定
	if (radiusAB >= (posAB.x + posAB.y + posAB.z)) {
		//自キャラの衝突時コールバック関数を呼び出す
		player_->OnCollisionSpring();
		//バネの衝突時コールバック関数を呼び出す
		gimmick_->OnCollisionSpring();
	}
#pragma endregion
#pragma region 自機と水流の当たり判定
	//自機の半径
	radiusA = 1.0f;
	//自機の座標
	posA = player_->GetWorldPosition();

	//自機と全水流の当たり判定
		//水流の半径
		radiusC = 5.0f;

		posC = gimmick_->GetWorldPositionWaterFlow();

		//座標A,Bの距離を求める
		posAC.x = (posC.x - posA.x) * (posC.x - posA.x);
		posAC.y = (posC.y - posA.y) * (posC.y - posA.y);
		posAC.z = (posC.z - posA.z) * (posC.z - posA.z);
		radiusAC = (radiusA + radiusC) * (radiusA + radiusC);

		//球と球の交差判定
		if (radiusAC >= (posAC.x + posAC.y + posAC.z)) {
			//自キャラの衝突時コールバック関数を呼び出す
			player_->OnCollisionWaterFlow();
			//バネの衝突時コールバック関数を呼び出す
			gimmick_->OnCollisionWaterFlow();
		}
	
#pragma endregion
}
