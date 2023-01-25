#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Collision.h"
#include <sstream>
#include <iomanip>
#include <cassert>
#include <random>

GameScene::~GameScene() {
	delete model_;
	// BGM解放
	//自キャラの解放
	delete player_;
	delete modelPlayer_;
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
	// インスタンス取得
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
	title_ = Sprite::Create(titleTexture_, { 0.0f, 0.0f });
	howtoplay_ = Sprite::Create(howToPlayTexture_, { 0.0f, 0.0f });
	stageClear_ = Sprite::Create(stageClearTexture_, { 0.0f, 0.0f });
	gameOver_ = Sprite::Create(gameOverTexture_, { 0.0f, 0.0f });
	gameClear_ = Sprite::Create(gameClearTexture_, { 0.0f, 0.0f });

	//自キャラの生成
	player_ = new Player();
	//天球データ生成
	skydome_ = new Skydome();
	// ステージ
	stage_ = new Stage();

	//天球データ初期化
	skydome_->Initialize(modelSkydome_);
	//自キャラの初期化
	player_->Initialize(modelPlayer_);
	// ステージの初期化
	stage_->Initialize(model_, filename_[0]);
	// マウスの初期化
	//mouse_->Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.eye = { 0.0f, 100.0f, -5.0f };
	viewProjection_.target = { 0.0f, -100.0f, 0.0f };
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	// シーン
	scene_ = DEBUG;
}

void GameScene::Update() {
	// シーン選択
	switch (scene_) {
#pragma region デバック
	case DEBUG:
		break;

#pragma endregion
#pragma region タイトル
	case TITLE:
		// スペースかマウス左クリックを押したら操作説明へ
		if (input_->TriggerKey(DIK_SPACE) || input_->IsTriggerMouse(0)) {
			// シーンを操作説明へ
			scene_ = INFO;
			// オーディオ再生
			//audio_->PlayWave(doneSe_);
		}
		
		break;
#pragma endregion
#pragma region 説明
	case INFO:
		// スペースかマウス左クリックを押したらステージへ
		if (input_->TriggerKey(DIK_SPACE) || input_->IsTriggerMouse(0)) {
			// シーンをステージへ
			scene_ = TUTORIAL;
			// オーディオ再生
			//audio_->PlayWave(doneSe_);

			// 初期化
			stage_->Initialize(model_, filename_[0]);	// ステージ読み込み(1)
			ownPhase_ = POP;			// 行動フェーズ(配置)
			enemyPhase_ = MOVE;	// 行動フェーズ(移動)
			turn_ = OWN;	// 自分のターン
		}

		break;
#pragma endregion
#pragma region チュートリアル
	case TUTORIAL:
		// 更新
		skydome_->Update();
		stage_->Update();

		// 選択しているブロックの座標を読み込む
		blockPos_ = stage_->GetBlockPosition(stage_->GetStageLine(), stage_->GetStageRow());
		blockPos_.y = 0;

		// ターン
		switch (turn_)
		{
		case OWN:
			// 自分のターンのアップデート
			player_->Update(blockPos_, ownPhase_);

			break;

		case ENEMY:

			break;
		}

		break;
#pragma endregion
	case STAGE1:
		// 更新
		skydome_->Update();
		stage_->Update();

		// 選択しているブロックの座標を読み込む
		blockPos_ = stage_->GetBlockPosition(stage_->GetStageLine(), stage_->GetStageRow());
		blockPos_.y = 0;

		// ターン
		switch (turn_)
		{
		case OWN:

			break;

		case ENEMY:

			break;
		}

		break;

	case STAGE2:
		// 更新
		skydome_->Update();
		stage_->Update();

		// 選択しているブロックの座標を読み込む
		blockPos_ = stage_->GetBlockPosition(stage_->GetStageLine(), stage_->GetStageRow());
		blockPos_.y = 0;

		// ターン
		switch (turn_)
		{
		case OWN:

			break;

		case ENEMY:

			break;
		}

		break;

	case STAGE3:
		// 更新
		skydome_->Update();
		stage_->Update();

		// 選択しているブロックの座標を読み込む
		blockPos_ = stage_->GetBlockPosition(stage_->GetStageLine(), stage_->GetStageRow());
		blockPos_.y = 0;

		// ターン
		switch (turn_)
		{
		case OWN:

			break;

		case ENEMY:

			break;
		}

		break;

	case CLEAR:
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(doneSe_);
			scene_ = TITLE;
			break;
		}
		break;

	case GAMEOVER:
		//スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			audio_->PlayWave(doneSe_);
			scene_ = TITLE;
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
	case DEBUG:
		break;

	case TITLE:
		break;

	case INFO:
		break;

	case TUTORIAL:
		break;

	case STAGE1:
		break;

	case STAGE2:
		break;

	case STAGE3:
		break;

	case CLEAR:
		break;

	case GAMEOVER:
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
	case DEBUG:
		stage_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		break;

	case TITLE:
		break;

	case INFO:
		break;

	case TUTORIAL:
		break;

	case STAGE1:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);
		stage_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;

	case STAGE2:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		stage_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;

	case STAGE3:
		// 3Dモデル描画
		skydome_->Draw(viewProjection_);

		stage_->Draw(viewProjection_);

		player_->Draw(viewProjection_);

		break;

	case CLEAR:
		break;

	case GAMEOVER:
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
	case DEBUG:
		break;

	case TITLE:
		//title_->Draw();
		break;

	case INFO:
		howtoplay_->Draw();
		break;

	case TUTORIAL:
		break;

	case STAGE1:

		break;

	case STAGE2:

		break;

	case STAGE3:

		break;

	case CLEAR:
		// gameClear_->Draw();
		break;

	case GAMEOVER:
		// gameOver_->Draw();
		break;
	}
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}