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
	delete modelskydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	modelskydome_ = Model::CreateFromOBJ("skydome", true);
	//自キャラの生成
	player_ = new Player();
	//敵キャラの生成
	enemy_ = new Enemy();
	//天球データ生成
	skydome_->Initialize(modelskydome_);
	//自キャラの初期化
	player_->Initialize(model_);
	//敵キャラの初期化
	enemy_->Initialize(model_);
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
	//天球データの更新処理
	skydome_->Update();
	//自キャラの更新処理
	player_->Update();
	//敵キャラの更新処理
	enemy_->Update();
	
	//当たり判定
	ChackAllCollisions();
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

	//デバック用表示
	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  "eye(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  "target(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
	  viewProjection_.target.z);

	debugText_->SetPos(50, 90);
	debugText_->Printf(
	  "up(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);

	debugText_->SetPos(50, 110);
	debugText_->Printf("fovAngleY(Degree):%f", MyMathUtility::GetDegree(viewProjection_.fovAngleY));

	debugText_->SetPos(50, 130);
	debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
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
	skydome_->Draw(viewProjection_);

	player_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);
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
	float radiusA = 1.0f;
	float radiusB = 1.0f;
	float radiiusAB;

	//自機弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();

	//敵弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetEnemyBullets();

#pragma region 自機と敵弾の当たり判定
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
			enemy_->OnCollision();
			//自機弾の衝突時コールバック関数を呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
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
}
