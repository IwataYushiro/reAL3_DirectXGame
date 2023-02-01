#pragma once
#include "SafeDelete.h"
#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "GlobalScene.h"
#include "Input.h"
#include "Player.h"
#include "Skydome/Skydome.h"
#include "Stage.h"
#include "Sprite.h"
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

	bool CollisionFlag(Player* p, Stage* s);

	size_t GetScene() { return scene_; }

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t titleTexture_ = 0;
	uint32_t howToPlayTexture_ = 0;
	uint32_t stageClearTexture_ = 0;
	uint32_t gameOverTexture_ = 0;
	uint32_t gameClearTexture_ = 0;

	// スプライト
	Sprite* title_ = nullptr;
	Sprite* howtoplay_ = nullptr;
	Sprite* stageClear_ = nullptr;
	Sprite* gameOver_ = nullptr;
	Sprite* gameClear_ = nullptr;

	//サウンドデータハンドル
	uint32_t titleBgm_ = 0;
	uint32_t doneSe_ = 0;
	//バネ
	uint32_t springSe_ = 0;

	// 3Dモデル
	Model* model_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;
	//カメラ上方向の角度
	float viewAngle = 0.0f;

	//自キャラ
	Player* player_ = nullptr;
	Player* player2_ = nullptr;
	
	Model* modelPlayer_ = nullptr;
	Model* modelPlayer2_ = nullptr;
	// 敵
	
	//天球データ
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	// ステージ
	Stage* stage_ = nullptr;

	// シーン用ファイルネーム
	const std::string filename_[4] = { "0", "1", "2", "3"};

	// シーン
	size_t scene_ = TITLE;
	
	//デバッグカメラ有効化
	bool isDebugCameraActive_ = false;
};
