#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "OptionBullet.h"
#include "WorldTransform.h"
#include <cassert>

//自機クラスの前方宣言
class Player;
//オプション(ガンダムでいうファンネルみたいな)
class Option {
  public:
	  //デストラクタ
	~Option();
	//初期化
	void Initialize(Model* model, const Vector3& position);
	//リセット処理
	void Reset(const Vector3& position);

	//更新
	void Update(ViewProjection& viewprojection);
	// 3Dレティクル
	void Reticle3D();
	//描画
	void Draw(ViewProjection& viewProjection);

	//オプションの移動処理
	void Move(ViewProjection& viewprojection);

	//オプションの旋回処理
	void Rotate();

	//オプションの攻撃処理
	void Attack();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//弾リストを取得
	const std::list<std::unique_ptr<OptionBullet>>& GetOptionBullets() { return optionBullets_; }

  private:
	//弾
	std::list<std::unique_ptr<OptionBullet>> optionBullets_;

	//ワールド変換データ
	WorldTransform worldTransform_;
	// 3Dレティクル用
	WorldTransform worldTransform3DReticle_;

	//モデル
	Model* model_ = nullptr;
	Model* modelBullet_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;
	//プレイヤーのデータ
	Player* player_ = nullptr;

	//インプット
	Input* input_ = nullptr;

	//デバッグテキスト
	DebugText* debugText_ = nullptr;
};
