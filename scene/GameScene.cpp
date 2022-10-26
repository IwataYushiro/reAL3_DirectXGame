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
	// ステージ
	delete stage_;
	// スプライト
	delete title_;
	delete howtoplay_;
	delete stageClear_;
	delete gameOver_;
	delete gameClear_;
}
 void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// BGMロード
	titleBgm_ = audio_->LoadWave("sound/title.wav");
	doneSe_ = audio_->LoadWave("sound/se/done.wav");

	audio_->PlayWave(titleBgm_, false, 0.1f);
	// 3Dモデルの生成
	model_ = Model::Create();
	//プレイヤー
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	//天球
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// テクスチャ読み込み
	titleTexture_ = TextureManager::Load("texture/title.png");
	howToPlayTexture_ = TextureManager::Load("texture/howtoplay.png");
	stageClearTexture_ = TextureManager::Load("texture/stageclear.png");
	gameOverTexture_ = TextureManager::Load("texture/gameover.png");
	gameClearTexture_ = TextureManager::Load("texture/gameclear.png");
	// スプライト
	title_ = Sprite::Create(titleTexture_, {0.0f, 0.0f});
	howtoplay_ = Sprite::Create(howToPlayTexture_, {0.0f, 0.0f});
	stageClear_= Sprite::Create(stageClearTexture_, {0.0f, 0.0f});
	gameOver_= Sprite::Create(gameOverTexture_, {0.0f, 0.0f});
	gameClear_= Sprite::Create(gameClearTexture_, {0.0f, 0.0f});

	//自キャラの生成
	player_ = new Player();
	//仕掛け生成
	gimmick_ = new Gimmick();
	//天球データ生成
	skydome_ = new Skydome();
	// ステージ
	stage_ = new Stage();

	//天球データ初期化
	skydome_->Initialize(modelSkydome_);
	//自キャラの初期化
	player_->Initialize(modelPlayer_);

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.eye = {20.0f, 5.0f, -60.0f};
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	// シーン
	scene_ = title;

	//仕掛けに自機のアドレスを渡す
	gimmick_->SetPlayer(player_);
	//仕掛け初期化
			gimmick_->Initialize();
}

void GameScene::Update() {
	switch (scene_) {
	case title:
		// スペースを押したら操作説明へ
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(doneSe_);
			scene_ = howtoplay;
			break;
		}

		break;

	case howtoplay:
		//天球データの更新処理
		skydome_->Update();
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(doneSe_);
			player_->Reset();
			scene_ = stage1;
			
			gimmick_->Initialize();
			// ステージ
			stage_->Initialize(model_, gimmick_, scene_);
			break;
		}
		break;

	case stage1:
		// プレイヤーが死んでいたら終了
		if (player_->IsDead()) {
			scene_ = gameover;
			break;
		}

		if (!stage_->GetEnd()) {
			//自キャラの更新処理
			player_->Update(viewProjection_);

			//天球データの更新処理
			skydome_->Update();
			// ステージ
			stage_->Update();
			//仕掛け更新
			gimmick_->Update();
		}
		// ステージクリア
		if (stage_->GetEnd()) {
			if (input_->TriggerKey(DIK_SPACE)) {
				audio_->PlayWave(doneSe_);
				player_->Reset();
				scene_ = stage2;
				
				gimmick_->Initialize();
				// ステージ
				stage_->Initialize(model_, gimmick_, scene_);
				break;
			}
		}

		//当たり判定
		ChackAllCollisions();
		break;

	case stage2:
		// プレイヤーが死んでいたら終了
		if (player_->IsDead()) {
			scene_ = gameover;
			break;
		}

		if (!stage_->GetEnd()) {
			//自キャラの更新処理
			player_->Update(viewProjection_);

			//天球データの更新処理
			skydome_->Update();
			// ステージ
			stage_->Update();
			//仕掛け更新
			gimmick_->Update();
		}
		// ステージクリア
		if (stage_->GetEnd()) {
			if (input_->TriggerKey(DIK_SPACE)) {
				audio_->PlayWave(doneSe_);
				player_->Reset();
				scene_ = stage3;
				
				gimmick_->Initialize();
				// ステージ
				stage_->Initialize(model_, gimmick_, scene_);
				break;
			}
		}

		//当たり判定
		ChackAllCollisions();
		break;

	case stage3:
		// プレイヤーが死んでいたら終了
		if (player_->IsDead()) {
			scene_ = gameover;
			break;
		}

		if (!stage_->GetEnd()) {
			//自キャラの更新処理
			player_->Update(viewProjection_);

			//天球データの更新処理
			skydome_->Update();
			// ステージ
			stage_->Update();
			//仕掛け更新
			gimmick_->Update();
		}
		// ステージクリア
		if (stage_->GetEnd()) {
			if (input_->TriggerKey(DIK_SPACE)) {
				audio_->PlayWave(doneSe_);
				scene_ = normalend;
				break;
			}
		}

		//当たり判定
		ChackAllCollisions();
		break;

	case normalend:
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(doneSe_);
			scene_ = title;
			break;
		}
		break;

	case trueend:
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(doneSe_);
			scene_ = title;
			break;
		}
		break;

	case gameover:
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(doneSe_);
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
	switch (scene_) {
	case title:
	case howtoplay:
	
		break;

	case stage1:

		break;

	case stage2:

		break;

	case stage3:

		break;

	case normalend:
		break;

	case trueend:
		break;

	case gameover:

		break;
	}
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

		break;

	case howtoplay:
		skydome_->Draw(viewProjection_);

		break;

	case stage1:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		stage_->Draw(viewProjection_);
		gimmick_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;

	case stage2:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		stage_->Draw(viewProjection_);
		gimmick_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;

	case stage3:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		stage_->Draw(viewProjection_);
		gimmick_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;

	case normalend:
		break;

	case trueend:
		break;

	case gameover:
		
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
	switch (scene_) {
	case title:

		title_->Draw();
		break;
	case howtoplay:
		howtoplay_->Draw();
		break;

	case stage1:
		if (stage_->GetEnd()) {
			stageClear_->Draw();
		}
		break;

	case stage2:
		if (stage_->GetEnd()) {
			stageClear_->Draw();
		}
		break;

	case stage3:
		if (stage_->GetEnd()) {
			stageClear_->Draw();
		}
		break;

	case normalend:
		gameClear_->Draw();
		break;

	case trueend:
		break;

	case gameover:
		gameOver_->Draw();
		break;
	}
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

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
	float radiusAB;

	//水流リストを取得
	const std::list<std::unique_ptr<WaterFlow>>& waterFlows = gimmick_->GetWaterFlow();

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
	//水流の半径
	radiusB = 1.0f;

	//自機の座標
	posA = player_->GetWorldPosition();

	//自機と全水流の当たり判定
	for (const std::unique_ptr<WaterFlow>& waterflow : waterFlows) {
		posB = waterflow->GetWorldPosition();

		//座標A,Bの距離を求める
		posAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		posAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		posAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		radiusAB = (radiusA + radiusB) * (radiusA + radiusB);

		//球と球の交差判定
		if (radiusAB >= (posAB.x + posAB.y + posAB.z)) {
			//自キャラの衝突時コールバック関数を呼び出す
			player_->OnCollisionWaterFlow();
			//水流の衝突時コールバック関数を呼び出す
			waterflow->OnCollision();
		}
	}
#pragma endregion
#pragma region 自機とステージブロックの当たり判定
	// 自機の座標
	posA = player_->GetWorldPosition();
	// ステージ用の自機の当たり判定の半径
	radiusA = 1.5f;
	// ステージブロックの半径
	radiusB = stage_->GetRadius();

	// ブロックと自機の当たり判定用の変数
	int block;
	// 矩形用の隅の座標p(自機)、b(ブロック)
	float pX1, pX2, pY1, pY2, pZ1, pZ2;
	float bX1, bX2, bY1, bY2, bZ1, bZ2;

	pX1 = posA.x - radiusA;
	pX2 = posA.x + radiusA;
	pY1 = posA.y - radiusA;
	pY2 = posA.y + radiusA;
	pZ1 = posA.z - radiusA;
	pZ2 = posA.z + radiusA;

	for (int i = 0; i < Stage::blockNum; i++) {
		// ステージブロックの座標、種類取得
		posB = stage_->GetWorldPosition(i);
		block = stage_->GetBlock(i);

		// ブロックの矩形座標
		bX1 = posB.x - radiusB;
		bX2 = posB.x + radiusB;
		bY1 = posB.y - radiusB;
		bY2 = posB.y + radiusB;
		bZ1 = posB.z - radiusB;
		bZ2 = posB.z + radiusB;

		// 当たり判定
		if (pX1 < bX2 && pX2 > bX1 && pY1 < bY2 && pY2 > bY1 && pZ1 < bZ2 && pZ2 > bZ1) {
			if (block == Stage::WALL) {
				if (posA.y < bY2 - 1.0f) {
					player_->OnCollisionWall();
					break;
				}
			}
			if (block == Stage::STEPUP) {
				if (posA.y >= bY2 + radiusA - 0.050f) {
					player_->OnCollisionBlock();
				} else {
					player_->OnCollisionStep();
				}
				break;
			}
			player_->OnCollisionBlock();
			break;
		}
		player_->OffCollisionBlock();
	}
#pragma endregion
}