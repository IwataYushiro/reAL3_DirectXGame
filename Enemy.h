#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "GlobalScene.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include <cassert>
#include <list>
#include <memory>

class Enemy {
public:
	// 列挙
	enum PIECE {
		NONE,
		PAWN,
		ROOK,
		BISHOP,
		KNIGHT,
		QUEEN,
		KING
	};

	// 構造体
	struct PieceData {
		WorldTransform worldTransform_;
		int type_;
	};

public:
	//初期化
	void Initialize(Model* model);

	//更新
	void Update(const Vector3& pos, int phase);

	//描画
	void Draw(ViewProjection& viewProjection);

	//リセット処理
	void Reset();

	// セレクト
	void Select();

private:
	//プレイヤーの移動処理
	void Move();

	// チェス駒生成
	void PopPlayer(const Vector3& pos);
	void PopPawn(const Vector3& pos);
	void PopRook();
	void PopBishop();
	void PopKnight();
	void PopQueen();
	void PopKing();

private:
	//インプット
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//音
	Audio* audio_ = nullptr;
	//サウンドデータ
	uint32_t jumpSound_ = 0;

	// ワールド変換データ
	std::list<std::unique_ptr<PieceData>> pieces_;

	// チェス駒
	std::list<std::unique_ptr<Pawn>> pawns_;
	std::list<std::unique_ptr<Rook>> rooks_;
	std::list<std::unique_ptr<Bishop>> bishops_;
	std::list<std::unique_ptr<Knight>> knights_;
	std::list<std::unique_ptr<Queen>> queen_;
	std::list<std::unique_ptr<King>> king_;

	// コスト
	int cost_ = 5;

	// Popコマンド用
	int popCommand_[16];
	int num_ = 0;

	//死亡フラグ
	bool isDead_ = false;
	//マウス
	bool mouseClick_;

public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
	int GetCost() { return cost_; }
};
