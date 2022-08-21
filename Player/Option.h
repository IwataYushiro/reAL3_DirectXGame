#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
//自機クラスの前方宣言
class Player;
//オプション(ガンダムでいうファンネルみたいな)
class Option {
  public:
	//初期化
	void Initialize(Model* model);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection& viewProjection);

	//オプションの移動処理
	void Move();

	//オプションの旋回処理
	void Rotate();

	//オプションの攻撃処理
	void Attack();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

  private:
	  
	//ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//プレイヤーのデータ
	Player* player_ = nullptr;
};
