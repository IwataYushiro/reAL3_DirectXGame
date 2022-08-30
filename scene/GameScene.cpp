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
	//自キャラの解放
	delete player_;

	//敵キャラの解放
	delete enemy_;
	//天球データ解放
	delete skydome_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//自キャラの生成
	player_ = new Player();

	//敵キャラの生成
	enemy_ = new Enemy();

	//天球データ生成
	skydome_ = new Skydome();

	//自キャラの初期化
	player_->Initialize(model_);

	//敵キャラの初期化
	enemy_->Initialize(model_);
	//天球データ初期化
	skydome_->Initialize(modelSkydome_);
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//敵に自機のアドレスを渡す
	enemy_->SetPlayer(player_);
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1260, 720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス無し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス無し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	switch (scene_) {
	case title:
		//天球データの更新処理
		skydome_->Update();

		debugText_->Print(" BIT SHOOTER", 200, 200, 3.0f);
		debugText_->Print(" SPACE Start", 200, 350, 2.0f);
		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = howtoplay;
			break;
		}
		break;

	case howtoplay:
		//天球データの更新処理
		skydome_->Update();

		debugText_->Print("WASD move player", 200, 200, 2.0f);
		debugText_->Print("MOUSE move option", 200, 250, 2.0f);
		debugText_->Print("MOUSE LEFT shot", 200, 300, 2.0f);

		debugText_->Print(" SPACE game start", 200, 450, 2.0f);
		if (input_->TriggerKey(DIK_SPACE)) {
			player_->Reset();
			enemy_->Reset();
			scene_ = stage1;
			break;
		}
		break;

	case stage1:
		if (!enemy_->IsDead()) {

			//天球データの更新処理
			skydome_->Update();
			//自キャラの更新処理
			player_->Update(viewProjection_);
			//敵キャラの更新処理
			enemy_->Update();

			if (player_->IsDead()) {
				scene_ = gameover;
				break;
			}
		}
		if (enemy_->IsDead()) {
			debugText_->Print("STAGE CLEAR", 300, 300, 3.0f);
			debugText_->Print(" SPACE next stage", 300, 400, 2.0f);
			debugText_->Print(" ESC title", 300, 450, 2.0f);
			if (input_->TriggerKey(DIK_SPACE)) {
				scene_ = clear;
				break;
			}
			if (input_->TriggerKey(DIK_ESCAPE)) {
				scene_ = title;
				break;
			}
		}

		//当たり判定
		ChackAllCollisions();
		break;

	case clear:
		debugText_->Print(" GAME CLEAR", 200, 200, 3.0f);
		debugText_->Print(" SPACE title", 200, 350, 2.0f);
		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = title;
			break;
		}
		break;

	case gameover:
		
		debugText_->Print(" GAME OVER", 200, 200, 3.0f);
		debugText_->Print(" SPACE title", 200, 350, 2.0f);
		if (input_->TriggerKey(DIK_SPACE)) {
			scene_ = title;
			break;
		}
		break;
	}

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C) && !isDebugCameraActive_) {
		isDebugCameraActive_ = true;
	}

#endif // _DEBUG

	if (isDebugCameraActive_) {
		//デバッグカメラの更新
		debugCamera_->Update();
		//ビュープロジェクション行列をコピー
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		////ビュープロジェクション行列を転送
		viewProjection_.TransferMatrix();
	} else {
		////ビュープロジェクション行列を再計算
		viewProjection_.UpdateMatrix();
		//ビュープロジェクション行列を転送
		viewProjection_.TransferMatrix();
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
		break;
	case howtoplay:
		break;
	case stage1:
		break;
	case clear:
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
		skydome_->Draw(viewProjection_);
		break;
	case howtoplay:
		skydome_->Draw(viewProjection_);
		break;
	case stage1:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		enemy_->Draw(viewProjection_);
		break;
	case clear:
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
		break;
	case howtoplay:
		break;
	case stage1:
		break;
	case clear:
		break;
	case gameover:
		break;
	}

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

	//自機弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	//オプションの弾リストを取得
	const std::list<std::unique_ptr<OptionBullet>>& optionBullets =
	  player_->GetOption()->GetOptionBullets();

	//敵弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetEnemyBullets();

#pragma region 自機と敵弾の当たり判定
	//それぞれの半径
	radiusA = 1.0f;
	radiusB = 1.0f;

	//自機の座標
	posA = player_->GetWorldPosition();

	//自機と全ての敵弾の当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		//敵弾の座標
		posB = bullet->GetWorldPosition();
		//座標A,Bの距離を求める
		posAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		posAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		posAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		radiiusAB = (radiusA + radiusB) * (radiusA + radiusB);

		//球と球の交差判定
		if (radiiusAB >= (posAB.x + posAB.y + posAB.z)) {
			//自キャラの衝突時コールバック関数を呼び出す
			player_->OnCollision();
			//敵弾の衝突時コールバック関数を呼び出す
			bullet->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵の当たり判定
	//それぞれの半径
	radiusA = 5.0f;
	radiusB = 1.0f;

	//敵の座標
	posA = enemy_->GetWorldPosition();

	//敵と全ての弾の当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
		//弾の座標
		posB = bullet->GetWorldPosition();
		//座標A,Bの距離を求める
		posAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		posAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		posAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		radiiusAB = (radiusA + radiusB) * (radiusA + radiusB);

		//球と球の交差判定
		if (radiiusAB >= (posAB.x + posAB.y + posAB.z)) {
			//敵キャラの衝突時コールバック関数を呼び出す
			enemy_->OnCollisionPlayer();
			//自機弾の衝突時コールバック関数を呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	//それぞれの半径
	radiusA = 1.0f;
	radiusB = 1.0f;

	for (const std::unique_ptr<PlayerBullet>& pBullet : playerBullets) {

		//自機弾の座標
		posA = pBullet->GetWorldPosition();

		for (const std::unique_ptr<EnemyBullet>& eBullet : enemyBullets) {

			//敵弾の座標
			posB = eBullet->GetWorldPosition();
			//座標A,Bの距離を求める
			posAB.x = (posB.x - posA.x) * (posB.x - posA.x);
			posAB.y = (posB.y - posA.y) * (posB.y - posA.y);
			posAB.z = (posB.z - posA.z) * (posB.z - posA.z);
			radiiusAB = (radiusA + radiusB) * (radiusA + radiusB);

			//球と球の交差判定
			if (radiiusAB >= (posAB.x + posAB.y + posAB.z)) {
				//自機弾の衝突時コールバック関数を呼び出す
				pBullet->OnCollision();
				//敵弾の衝突時コールバック関数を呼び出す
				eBullet->OnCollision();
			}
		}
	}
#pragma endregion

#pragma region オプション弾と敵の当たり判定
	//それぞれの半径
	radiusA = 5.0f;
	radiusB = 1.0f;

	//敵の座標
	posA = enemy_->GetWorldPosition();

	//敵と全ての弾の当たり判定
	for (const std::unique_ptr<OptionBullet>& bullet : optionBullets) {
		//弾の座標
		posB = bullet->GetWorldPosition();
		//座標A,Bの距離を求める
		posAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		posAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		posAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		radiiusAB = (radiusA + radiusB) * (radiusA + radiusB);

		//球と球の交差判定
		if (radiiusAB >= (posAB.x + posAB.y + posAB.z)) {
			//敵キャラの衝突時コールバック関数を呼び出す
			enemy_->OnCollisionOption();
			//オプション弾の衝突時コールバック関数を呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region オプション弾と敵弾の当たり判定
	//それぞれの半径
	radiusA = 1.0f;
	radiusB = 1.0f;

	for (const std::unique_ptr<OptionBullet>& oBullet : optionBullets) {

		//自機弾の座標
		posA = oBullet->GetWorldPosition();

		for (const std::unique_ptr<EnemyBullet>& eBullet : enemyBullets) {

			//敵弾の座標
			posB = eBullet->GetWorldPosition();
			//座標A,Bの距離を求める
			posAB.x = (posB.x - posA.x) * (posB.x - posA.x);
			posAB.y = (posB.y - posA.y) * (posB.y - posA.y);
			posAB.z = (posB.z - posA.z) * (posB.z - posA.z);
			radiiusAB = (radiusA + radiusB) * (radiusA + radiusB);

			//球と球の交差判定
			if (radiiusAB >= (posAB.x + posAB.y + posAB.z)) {
				//オプション弾の衝突時コールバック関数を呼び出す
				oBullet->OnCollision();
				//敵弾の衝突時コールバック関数を呼び出す
				eBullet->OnCollision();
			}
		}
	}
#pragma endregion
}
