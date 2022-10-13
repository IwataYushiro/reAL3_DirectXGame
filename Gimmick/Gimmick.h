#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

//自機クラスの前方宣言
class Player;

class Gimmick {
  public:
	Gimmick();
	~Gimmick();

	//
	//水流をパーティクル生成するための変数
	static const int WATERFLOW_MAX_ = 500; //最大個数

	//全体初期化
	void Initialize();
	//バネ初期化
	void InitializeSpring();
	//水流初期化
	void InitializeWaterFlow();

	//全体更新
	void Update();
	//水流更新
	void UpdateWaterFlow();

	//全体描画
	void Draw(ViewProjection& viewProjection);
	//バネ描画
	void DrawSpring(ViewProjection& viewProjection);
	//水流描画
	void DrawWaterFlow(ViewProjection& viewProjection);
	
	//各仕掛けのワールド座標を取得
	Vector3 GetWorldPositionSpring();

	Vector3& GetWorldPositionWaterFlow();

  private:
	//バネ
	//ワールド変換データ
	WorldTransform worldTransformSpring_;
	//モデルデータ
	Model* modelSpring_ = nullptr; //バネ

	//水流
	
	//ワールド変換データ
	WorldTransform worldTransformWaterFlow_[WATERFLOW_MAX_];
	//モデルデータ
	Model* modelWaterFlow_ = nullptr; //水流

	float waterFlowWidth_;							//横幅
	float waterFlowHeight_;							//縦幅
	//float waterFlowRadius;						//半径
	float waterFlowSpeed_;							//速度
	int waterFlowBright_[WATERFLOW_MAX_];			//明るさ
	bool isActiveWaterFlow_[WATERFLOW_MAX_];		//生きてるか

	//プレーヤーデータ
	Player* player_ = nullptr;

  public:
	//プレーヤーセット
	void SetPlayer(Player* player) { player_ = player; }
	//バネ
	void OnCollisionSpring();
	//水流
	void OnCollisionWaterFlow();
	float GetWaterFlowSpeed() { return waterFlowSpeed_; }
	static const int GetWaterFlowMaxInit() { return WATERFLOW_MAX_; }
};
