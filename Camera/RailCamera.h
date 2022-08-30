#pragma once
#include "DebugText.h"
#include "MyMathUtility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

//レールカメラ
class RailCamera {
  public:
	  //初期化
	void Initialize(WorldTransform& worldTransform);
	//リセット
	void Reset();
	//更新
	void Update();

	//描画
	void Draw();

	void SetWorldTransform(WorldTransform& worldTransform) { worldTransform_ = worldTransform; };
	void SetWorldPosition(Vector3& position) { worldTransform_.translation_ = position; };
	void SetWorldRotation(Vector3& rotation) { worldTransform_.rotation_ = rotation; };

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//回転角(度数)
	Vector3 decAngle;
	//回転角(カメラ)
	Vector3 cameraAngle;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};