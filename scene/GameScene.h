#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "GlobalScene.h"
#include "Input.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Skydome/Skydome.h"
#include "Sprite.h"
#include "Stage.h"
#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
  public: // メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool CollisionStageFlag(Player* p, Stage* s);
	bool CollisionPlayerFlag(Player* p1, Player* p2);

	size_t GetScene() { return scene_; }

	void Parameter(const Vector3& playerPos1, const Vector3& playerPos2, const int& stageNum);

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	// テクスチャハンドル
	uint32_t titleTexture_ = 0;
	uint32_t howToPlayTexture_ = 0;
	uint32_t stageClearTexture_ = 0;
	uint32_t gameOverTexture_ = 0;
	uint32_t gameClearTexture_ = 0;

	// 背景用
	uint32_t backGroundTexture1 = 0;
	uint32_t backGroundTexture2 = 0;
	uint32_t backGroundTexture3 = 0;
	uint32_t backGroundTexture4 = 0;
	uint32_t backGroundTexture5 = 0;
	uint32_t backGroundTexture6 = 0;
	// スプライト
	Sprite* title_ = nullptr;
	Sprite* howtoplay_ = nullptr;
	Sprite* stageClear_ = nullptr;
	Sprite* gameOver_ = nullptr;
	Sprite* gameClear_ = nullptr;

	// 背景
	Sprite* backGround1_ = nullptr;
	Sprite* backGround2_ = nullptr;
	Sprite* backGround3_ = nullptr;
	Sprite* backGround4_ = nullptr;
	Sprite* backGround5_ = nullptr;
	Sprite* backGround6_ = nullptr;

	// サウンドデータハンドル
	uint32_t titleBgm_ = 0;
	uint32_t doneSe_ = 0;
	// バネ
	uint32_t springSe_ = 0;

	// 3Dモデル
	Model* model_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;
	// カメラ上方向の角度
	float viewAngle = 0.0f;

	// 自キャラ
	Player* player_ = nullptr;
	Player* player2_ = nullptr;

	// モデル
	Model* modelPlayer_ = nullptr;
	Model* modelPlayer2_ = nullptr;

	// 天球データ
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	// ステージ
	Stage* stage_ = nullptr;

	// シーン用ファイルネーム
	const std::string filename_[7] = {
	  "0",
	  "1",
	  "2",
	  "3",
	  "4",
	  "5",
	  "6"}; // 0は使わない

	// シーン
	size_t scene_ = TITLE;

	// デバッグカメラ有効化
	bool isDebugCameraActive_ = false;
	// クリアしたか
	bool isClear = false;
};
