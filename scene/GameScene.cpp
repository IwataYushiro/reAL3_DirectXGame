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
	//天球データ生成
	skydome_ = new Skydome();

	//自キャラの初期化
	player_->Initialize(modelPlayer_);
	//天球データ初期化
	skydome_->Initialize(modelSkydome_);
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	scene_ = title;
}

void GameScene::Update() {
	switch (scene_) {
	case title:
		//天球データの更新処理
		skydome_->Update();

		//自キャラの更新処理
		player_->Update(viewProjection_);

		/*debugText_->Print(" BIT SHOOTER", 200, 200, 3.0f);
		debugText_->Print(" SPACE start", 200, 350, 2.0f);*/
		/*if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = howtoplay;
			break;
		}*/
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
	// A,Bの座標の距離用
	Vector3 posAB;
	//判定対象A,Bの半径
	float radiusA;
	float radiusB;
	float radiiusAB;
}
