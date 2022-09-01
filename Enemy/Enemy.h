#pragma once
#include "DebugText.h"
#include "EnemyBullet.h"
#include "GlobalScene.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>
//自機クラスの前方宣言
class Player;
//ゲームシーンも
class GameScene;
//敵
class Enemy {
  public:
	~Enemy();
	//弾発射間隔
	static const int kFireIntervalStage1 = 40;
	static const int kFireIntervalStage2 = 60;
	static const int kFireIntervalStage3 = 30;
	//初期化
	void Initialize(Model* model);

	//リセット処理
	void Reset();
	void EndingPosition();
	//パラメータ
	void Stage1Parameter();
	void Stage2Parameter();
	void Stage3Parameter();
	//更新
	void Update();
	//弾発射
	void Fire();
	//ワールド座標を取得
	Vector3 GetWorldPosition();
	//描画
	void DrawStage1(const ViewProjection& viewProjection);
	void DrawStage2(const ViewProjection& viewProjection);
	void DrawStage3(const ViewProjection& viewProjection);

	//状態変化用の更新関数
	//接近
	void UpdateApproachStage1();
	void UpdateApproachStage2();
	void UpdateApproachStage3();
	//攻撃
	void UpdateAttackStage1();
	void UpdateAttackStage2();
	void UpdateAttackStage3();
	//離脱
	void UpdateLeave();

	//ステージ3限定離脱
	void UpdateSaveStage3();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollisionPlayer();
	void OnCollisionOption();

	//弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() { return enemyBullets_; }

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//弾
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//インプット
	Input* input_ = nullptr;
	//デバックテキスト
	DebugText* debugText_ = nullptr;
	//モデル
	Model* modelStage1_ = nullptr;
	Model* modelDeadStage1_ = nullptr;

	Model* modelStage2_ = nullptr;
	Model* modelDeadStage2_ = nullptr;

	Model* modelStage3_ = nullptr;
	Model* modelSaveStage3_ = nullptr;

	Model* modelBullet_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//行動フェーズ
	enum class Phase {
		//ここからステージ1
		ApproachStage1, //接近
		AttackStage1,   //攻撃

		//ここからステージ2
		ApproachStage2, //接近
		AttackStage2,   //攻撃

		//ここからステージ3
		ApproachStage3, //接近
		AttackStage3,   //攻撃
		SaveStage3,     //ステージ3限定
		//全体
		Leave, //離脱
		//エンディング
		end,
	};

	//フェーズ
	Phase phase_;
	//弾発射タイマー
	int32_t fireTimer = 0;

	//自機
	Player* player_ = nullptr;
	//ゲームシーン
	GameScene* gameScene_ = nullptr;

	//死亡フラグとライフ
	bool isDead_;
	int life_;

	//反転フラグ
	bool isReverse_ = false;

  public:
	bool IsDead() const { return isDead_; }
	void SetPlayer(Player* player) { player_ = player; }
};
