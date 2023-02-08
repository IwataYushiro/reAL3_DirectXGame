#include "GameScene.h"
#include "AxisIndicator.h"
#include "Collision.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <iomanip>
#include <random>
#include <sstream>

GameScene::~GameScene() {
	delete model_;
	// BGM解放
	// 自キャラの解放
	delete player_;
	delete player2_;
	delete modelPlayer_;
	delete modelPlayer2_;
	// 天球データ解放
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
	// 背景スプライト
	delete backGround1_;
	delete backGround2_;
	delete backGround3_;
	delete backGround4_;
	delete backGround5_;
	delete backGround6_;
}
void GameScene::Initialize() {
	// インスタンス取得
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	// プレイヤー
	modelPlayer_ = Model::CreateFromOBJ("bplayer", true);
	modelPlayer2_ = Model::CreateFromOBJ("wplayer", true);
	// 天球
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// テクスチャ読み込み
	titleTexture_ = TextureManager::Load("texture/title.png");
	howToPlayTexture_ = TextureManager::Load("texture/howtoplay.png");
	stageClearTexture_ = TextureManager::Load("texture/stageclear.png");
	gameOverTexture_ = TextureManager::Load("texture/gameover.png");
	gameClearTexture_ = TextureManager::Load("texture/gameclear.png");
	backGroundTexture1 = TextureManager::Load("texture/background1.png");
	backGroundTexture2 = TextureManager::Load("texture/background2.png");
	backGroundTexture3 = TextureManager::Load("texture/background3.png");
	backGroundTexture4 = TextureManager::Load("texture/background4.png");
	backGroundTexture5 = TextureManager::Load("texture/background5.png");
	backGroundTexture6 = TextureManager::Load("texture/background6.png");

	// スプライト
	title_ = Sprite::Create(titleTexture_, {0.0f, 0.0f});
	howtoplay_ = Sprite::Create(howToPlayTexture_, {0.0f, 0.0f});
	stageClear_ = Sprite::Create(stageClearTexture_, {0.0f, 0.0f});
	gameOver_ = Sprite::Create(gameOverTexture_, {0.0f, 0.0f});
	gameClear_ = Sprite::Create(gameClearTexture_, {0.0f, 0.0f});
	backGround1_ = Sprite::Create(backGroundTexture1, {0.0f, 0.0f});
	backGround2_ = Sprite::Create(backGroundTexture2, {0.0f, 0.0f});
	backGround3_ = Sprite::Create(backGroundTexture3, {0.0f, 0.0f});
	backGround4_ = Sprite::Create(backGroundTexture4, {0.0f, 0.0f});
	backGround5_ = Sprite::Create(backGroundTexture5, {0.0f, 0.0f});
	backGround6_ = Sprite::Create(backGroundTexture6, {0.0f, 0.0f});

	// BGMロード
	titleBgm_ = audio_->LoadWave("sound/title.wav");
	doneSe_ = audio_->LoadWave("sound/se/done.wav");

	audio_->PlayWave(titleBgm_, true, 0.7f);

	// 自キャラの生成
	player_ = new Player();
	player2_ = new Player();
	// 天球データ生成
	skydome_ = new Skydome();
	// ステージ
	stage_ = new Stage();
	
	// 天球データ初期化
	skydome_->Initialize(modelSkydome_);

	// ステージの初期化
	stage_->Initialize(model_);
// 初期化
	Parameter({14.0f, -10.0f, 54.0f}, {38.0f, -10.0f, 26.0f}, 1);
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.eye = {40.0f, 70.0f, -30.0f};
	viewProjection_.target = {40.0f, 20.0f, 10.0f};
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	// シーン
	scene_ = TITLE;
}

void GameScene::Update() {
	// シーン選択
	switch (scene_) {

#pragma region タイトル
	case TITLE:
		// スペースかマウス左クリックを押したら操作説明へ
		if (input_->TriggerKey(DIK_SPACE) || input_->IsTriggerMouse(0)) {
			
			//初期化
			Parameter({14.0f, -10.0f, 54.0f}, {38.0f, -10.0f, 26.0f}, 1);
			// シーンを操作説明へ
			scene_ = INFO;
			
			// オーディオ再生
			// audio_->PlayWave(doneSe_);
			
			break;
		}

		break;
#pragma endregion
#pragma region 説明
	case INFO:
		// スペースかマウス左クリックを押したらステージへ
		if (input_->TriggerKey(DIK_SPACE) || input_->IsTriggerMouse(0)) {
			
			// シーンをステージへ
			scene_ = STAGE1;
			// オーディオ再生
			// audio_->PlayWave(doneSe_);
			break;
		}

		break;
#pragma endregion
	case STAGE1:

		if (stage_->GetIsGoal() && CollisionPlayerFlag(player_, player2_)) {
			isClear = true;
		}
		if (isClear) {
			if (input_->TriggerKey(DIK_SPACE)) {
				Parameter({18.0f, -10.0f, 14.0f}, {58.0f, -10.0f, 30.0f}, 2);
				scene_ = STAGE2;
				break;
			}
		} 
		else 
		{
			if (input_->TriggerKey(DIK_R)) 
			{
				Reset({14.0f, -10.0f, 54.0f}, {38.0f, -10.0f, 26.0f});
			}
		}

		stage_->Update();

		CollisionStageFlag(player_, stage_);
		CollisionStageFlag(player2_, stage_);

		player_->Update();
		player2_->Update();
		player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
		player2_->OnCollisionStage(CollisionStageFlag(player2_, stage_));
		Player::OnCollisionPlayer(CollisionPlayerFlag(player_, player2_));

		break;

	case STAGE2:
		if (stage_->GetIsGoal() && CollisionPlayerFlag(player_, player2_)) {
			isClear = true;
		}
		if (isClear) {
			if (input_->TriggerKey(DIK_SPACE)) {
				Parameter({2.0f, -10.0f, 54.0f}, {54.0f, -10.0f, 78.0f}, 3);
				scene_ = STAGE3;
				break;
			}
		} else {
			if (input_->TriggerKey(DIK_R)) {
				Reset({18.0f, -10.0f, 14.0f}, {58.0f, -10.0f, 30.0f});
			}
		}
		stage_->Update();

		CollisionStageFlag(player_, stage_);
		CollisionStageFlag(player2_, stage_);

		player_->Update();
		player2_->Update();
		player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
		player2_->OnCollisionStage(CollisionStageFlag(player2_, stage_));
		Player::OnCollisionPlayer(CollisionPlayerFlag(player_, player2_));

		break;

	case STAGE3:
		if (stage_->GetIsGoal() && CollisionPlayerFlag(player_, player2_)) {
			isClear = true;
		}
		if (isClear) {
			if (input_->TriggerKey(DIK_SPACE)) {
				Parameter({14.0f, -10.0f, 78.0f}, {54.0f, -10.0f, 58.0f}, 4);
				scene_ = STAGE4;
				break;
			}
		} else {
			if (input_->TriggerKey(DIK_R)) {
				Reset({2.0f, -10.0f, 54.0f}, {54.0f, -10.0f, 78.0f});
			}
		}
		stage_->Update();

		CollisionStageFlag(player_, stage_);
		CollisionStageFlag(player2_, stage_);

		player_->Update();
		player2_->Update();
		player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
		player2_->OnCollisionStage(CollisionStageFlag(player2_, stage_));
		Player::OnCollisionPlayer(CollisionPlayerFlag(player_, player2_));

		break;
	case STAGE4:
		if (stage_->GetIsGoal() && CollisionPlayerFlag(player_, player2_)) {
			isClear = true;
		}
		if (isClear) {
			if (input_->TriggerKey(DIK_SPACE)) {
				Parameter({34.0f, -10.0f, 6.0f}, {62.0f, -10.0f, 50.0f}, 5);
				scene_ = STAGE5;
				break;
			}
		} else {
			if (input_->TriggerKey(DIK_R)) {
				Reset({14.0f, -10.0f, 78.0f}, {54.0f, -10.0f, 58.0f});
			}
		}
		stage_->Update();

		CollisionStageFlag(player_, stage_);
		CollisionStageFlag(player2_, stage_);

		player_->Update();
		player2_->Update();
		player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
		player2_->OnCollisionStage(CollisionStageFlag(player2_, stage_));
		Player::OnCollisionPlayer(CollisionPlayerFlag(player_, player2_));

		break;
	case STAGE5:
		if (stage_->GetIsGoal() && CollisionPlayerFlag(player_, player2_)) {
			isClear = true;
		}
		if (isClear) {
			if (input_->TriggerKey(DIK_SPACE)) {
				Parameter({10.0f, -10.0f, 78.0f}, {74.0f, -10.0f, 38.0f}, 6);
				scene_ = STAGE6;
				break;
			}
		} else {
			if (input_->TriggerKey(DIK_R)) {
				Reset({34.0f, -10.0f, 6.0f}, {62.0f, -10.0f, 50.0f});
			}
		}
		stage_->Update();

		CollisionStageFlag(player_, stage_);
		CollisionStageFlag(player2_, stage_);

		player_->Update();
		player2_->Update();
		player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
		player2_->OnCollisionStage(CollisionStageFlag(player2_, stage_));
		Player::OnCollisionPlayer(CollisionPlayerFlag(player_, player2_));

		break;
	case STAGE6:
		if (stage_->GetIsGoal() && CollisionPlayerFlag(player_, player2_)) {
			isClear = true;
		}
		if (isClear) {
			if (input_->TriggerKey(DIK_SPACE)) {
				scene_ = CLEAR;
				isClear = false;
				break;
			}
		} else {
			if (input_->TriggerKey(DIK_R)) {
				Reset({10.0f, -10.0f, 78.0f}, {74.0f, -10.0f, 38.0f});
			}
		}
		stage_->Update();

		CollisionStageFlag(player_, stage_);
		CollisionStageFlag(player2_, stage_);

		player_->Update();
		player2_->Update();
		player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
		player2_->OnCollisionStage(CollisionStageFlag(player2_, stage_));
		Player::OnCollisionPlayer(CollisionPlayerFlag(player_, player2_));

		break;

	case CLEAR:
		// スペースキーでタイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			
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
	case TITLE:
		break;

	case INFO:
		break;

	case STAGE1:
		backGround1_->Draw();
		break;

	case STAGE2:
		backGround2_->Draw();
		break;

	case STAGE3:
		backGround3_->Draw();
		break;
	case STAGE4:
		backGround4_->Draw();
		break;
	case STAGE5:
		backGround5_->Draw();
		break;
	case STAGE6:
		backGround6_->Draw();
		break;
	case CLEAR:
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
	case TITLE:
		break;

	case INFO:
		break;

	case STAGE1:
		stage_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		player2_->Draw(viewProjection_);

		break;

	case STAGE2:
		stage_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		player2_->Draw(viewProjection_);

		break;

	case STAGE3:
		stage_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		player2_->Draw(viewProjection_);
		break;
	case STAGE4:
		stage_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		player2_->Draw(viewProjection_);
		break;
	case STAGE5:
		stage_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		player2_->Draw(viewProjection_);
		break;
	case STAGE6:
		stage_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		player2_->Draw(viewProjection_);
		break;
	case CLEAR:
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
	case TITLE:
		title_->Draw();
		break;

	case INFO:
		howtoplay_->Draw();
		break;

	case STAGE1:

		break;

	case STAGE2:

		break;

	case STAGE3:

		break;
	case STAGE4:

		break;
	case STAGE5:

		break;
	case STAGE6:

		break;
	case CLEAR:
		gameClear_->Draw();
		break;

	}

	if (isClear) {
		stageClear_->Draw();
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

bool GameScene::CollisionStageFlag(Player* p, Stage* s) {
	// 各座標変数の宣言
	Vector3 pPos = p->GetPosition();
	float pRadius = p->GetRadius();
	float pX1, pX2, pZ1, pZ2;
	// プレイヤーの矩形座標
	pX1 = pPos.x - pRadius;
	pX2 = pPos.x + pRadius;
	pZ1 = pPos.z - pRadius;
	pZ2 = pPos.z + pRadius;

	// プレイヤーLeftTop座標
	int pLT[2] = {static_cast<int>(pX1 / 4), static_cast<int>(((pZ1 / 4) - 19) * -1)};
	int isFloor = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			// 足元のブロックを判別
			if (s->CheckFloorBlock(pLT[0] + i, pLT[1] + j)) {
				isFloor++;
			}
			if (isFloor == 4) {
				p->IsDead();
			}
			s->CheckBlock(pLT[0] + i, pLT[1] + j);
			// 各座標変数の宣言
			Vector3 bPos = s->GetBlockPosition(pLT[0] + i, pLT[1] + j);
			float bRadius = s->GetRadius();
			float bX1, bX2, bZ1, bZ2;
			// ブロックの矩形座標
			bX1 = bPos.x - bRadius;
			bX2 = bPos.x + bRadius;
			bZ1 = bPos.z - bRadius;
			bZ2 = bPos.z + bRadius;

			// 当たり判定
			if (pX1 < bX2 && pX2 > bX1 && pZ1 < bZ2 && pZ2 > bZ1) {
				return true;
			}
		}
	}
	return false;
}

bool GameScene::CollisionPlayerFlag(Player* p1, Player* p2) {
	// 各座標変数の宣言
	Vector3 pPos1 = p1->GetPosition();
	float pRadius1 = p1->GetRadius();
	float p1X1, p1X2, p1Z1, p1Z2;
	// プレイヤーの矩形座標
	p1X1 = pPos1.x - pRadius1;
	p1X2 = pPos1.x + pRadius1;
	p1Z1 = pPos1.z - pRadius1;
	p1Z2 = pPos1.z + pRadius1;

	Vector3 pPos2 = p2->GetPosition();
	float pRadius2 = p2->GetRadius();
	float p2X1, p2X2, p2Z1, p2Z2;
	// プレイヤーの矩形座標
	p2X1 = pPos2.x - pRadius2;
	p2X2 = pPos2.x + pRadius2;
	p2Z1 = pPos2.z - pRadius2;
	p2Z2 = pPos2.z + pRadius2;
	// 当たり判定
	if (p1X1 < p2X2 && p1X2 > p2X1 && p1Z1 < p2Z2 && p1Z2 > p2Z1) {
		return true;
	}
	return false;
}

void GameScene::Parameter(
  const Vector3& playerPos1, const Vector3& playerPos2, const int& stageNum) {
	// 自キャラの初期化
	Vector3 pos1 = playerPos1;
	Vector3 pos2 = playerPos2;
	player_->Initialize(modelPlayer_, pos1);
	player2_->Initialize(modelPlayer2_, pos2);
	// ステージの初期化
	stage_->StageInitialize(filename_[stageNum]); // ステージ読み込み(1)

	isClear = false;
}

void GameScene::Reset(const Vector3& playerPos1, const Vector3& playerPos2) {
	// 自キャラの再初期化
	Vector3 pos1 = playerPos1;
	Vector3 pos2 = playerPos2;

	player_->Initialize(modelPlayer_, pos1);
	player2_->Initialize(modelPlayer2_, pos2);
}
