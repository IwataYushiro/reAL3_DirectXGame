#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	Vector3 cubeBaseVertex[8]= {
	  {0.0f, 5.0f, 0.0f},
      {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
	  {0.0f, 5.0f, 5.0f},
      {0.0f, 0.0f, 5.0f},
      {5.0f, 0.0f, 5.0f},
      {5.0f, 5.0f, 5.0f}
    };
	//原点移動、平行移動、回転、拡大の行列の宣言
	Vector3 cubeOriginVertex[8];
	Vector3 cubeMoveVertex[8];
	Vector3 cubeRotatedVertex[8];
	Vector3 cubeScaledVertex[8];

	int baseEdgeList[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},
      {4, 5},
      {5, 6},
	  {6, 7},
      {7, 4},
      {0, 4},
      {1, 5},
      {2, 6},
      {3, 7}
    };

	Vector4 baseColor = {0xFF, 0xFF, 0xFF, 0xFF};
	Vector4 moveColor = {0xFF, 0x00, 0x00, 0xFF};

	Vector4 affinMove[4] = {
	  {1.0f, 0.0f, 0.0f, 10.0f},
	  {0.0f, 1.0f, 0.0f, 10.0f},
	  {0.0f, 0.0f, 1.0f, 10.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f }
    };
	//アフィン変換

	/// <summary>
  /// ゲームシーン用
  /// </summary>
	};
