#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//自機クラスの前方宣言
class Player;

class Gimmick {
  public:
	Gimmick();
	~Gimmick();

	//
	//全体初期化
	void Initialize();
	//バネ初期化
	void InitializeSpring();
	
	//全体更新
	void Update();
	//バネ更新
	void UpdateSpring();
	
	//全体描画
	void Draw(ViewProjection& viewProjection);
	//バネ描画
	void DrawSpring(ViewProjection& viewProjection);

	//各仕掛けのワールド座標を取得
	Vector3 GetWorldPositionSpring();
  private:
	//ワールド変換データ
	WorldTransform worldTransformSpring_;
	//バネ
	Vector3 SpringPos_;
	//モデルデータ
	Model* modelSpring_ = nullptr;	//バネ
	//プレーヤーデータ
	Player* player_ = nullptr;
	public:
	//プレーヤーセット
	void SetPlayer(Player* player) { player_ = player; }
	  void OnCollisionSpring();
};
