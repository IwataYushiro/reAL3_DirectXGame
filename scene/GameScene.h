#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "GlobalScene.h"
#include "Gimmick.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Skydome/Skydome.h"
#include "Stage.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

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

	size_t GetScene() { return scene_; }

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//サウンドデータハンドル
	uint32_t titleBgm_ = 0;
	uint32_t doneSe_ = 0;
	//バネ
	uint32_t springSe_ = 0;
	
	//テクスチャハンドル
	
	uint32_t titleTexture_ = 0;
	uint32_t howToPlayTexture_ = 0;
	uint32_t stageClearTexture_ = 0;
	uint32_t gameOverTexture_ = 0;
	uint32_t gameClearTexture_ = 0;

	// スプライト
	Sprite* title_;
	Sprite* howtoplay_;
	Sprite* stageClear_;
	Sprite* gameOver_;
	Sprite* gameClear_;

	// 3Dモデル
	Model* model_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;
	//カメラ上方向の角度
	float viewAngle = 0.0f;

	//自キャラ
	Player* player_ = nullptr;
	Model* modelPlayer_ = nullptr;
	//天球データ
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	// ステージ
	Stage* stage_ = nullptr;

	// シーン
	size_t scene_;
	// シーン用ファイルネーム
	const std::string filename_[3] = { "1", "2", "3" };

	// アクション
	ActionData action_;
	
	//デバッグカメラ有効化
	bool isDebugCameraActive_ = false;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
