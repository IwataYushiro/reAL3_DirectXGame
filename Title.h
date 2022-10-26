#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

#include "TextureManager.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

#include "Clear.h"
#include "GameOver.h"

#include "Scene.h"

class Title
{
public: // メンバ関数
/// <summary>
/// コンストクラタ
/// </summary>
	Title();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Title();

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

	void Reset();

	oScene GetNextScene() { return nextScene_; }

	int GetChangeFlag() { return changeFlag_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	// シーン切り替え
	oScene nextScene_ = oScene::TITLE;
	// 切り替えフラグ
	bool changeFlag_ = false;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// スプライト
	Sprite* sprite_ = nullptr;
};