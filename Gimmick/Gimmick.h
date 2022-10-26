#pragma once
#include "Audio.h"
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <cassert>
#include "WaterFrow.h"
#include <list>
#include <memory>

//自機クラスの前方宣言
class Player;

class Gimmick {
  public:
	Gimmick();
	~Gimmick();

	//全体初期化
	void Initialize();
	//バネ初期化
	void InitializeSpring();
	
	//全体更新
	void Update();
	
	//全体描画
	void Draw(ViewProjection& viewProjection);
	//バネ描画
	void DrawSpring(ViewProjection& viewProjection);
	
	//各仕掛けのワールド座標を取得
	Vector3 GetWorldPositionSpring();

	//水流リストを取得
	const std::list<std::unique_ptr<WaterFlow>>& GetWaterFlow() { return waterFlow_; }
  private:
	//音
	Audio* audio_ = nullptr;
	
	//バネ
	uint32_t springSe_ = 0;
	//ワールド変換データ
	WorldTransform worldTransformSpring_;
	
	//テクスチャ
	uint32_t texSpring_ = 0;
	//モデルデータ
	Model* modelSpring_ = nullptr; //バネ

	//水流
	std::list<std::unique_ptr<WaterFlow>> waterFlow_;
	Vector3 waterFlowPosition_;
	//プレーヤーデータ
	Player* player_ = nullptr;

  public:
	//プレーヤーセット
	void SetPlayer(Player* player) { player_ = player; }
	//バネ
	void OnCollisionSpring();
	
	void SetWorldPositionSpring(Vector3 position) { worldTransformSpring_.translation_ = position; }

	void SetPositionWaterFlow(Vector3 position) { waterFlowPosition_ = position; }
};
