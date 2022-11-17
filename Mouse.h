#pragma once
#include "Input.h"
#include "DebugText.h"
#include "CollisionPrimitive.h"
#include "Collision.h"
#include "Vector3.h"
#include "Model.h"
#include "WorldTransform.h"
#include <DirectXMath.h>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <ViewProjection.h>

class Mouse
{
public:
	void Initialize(ViewProjection& viewProjection);

	void Update(ViewProjection& viewProjection);

	void Draw(ViewProjection& viewProjection);

	Matrix4 Viewport(float VpWidth,float VpHeight);
private:
	//インプット
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;
	// モデル
	Model* model_ = nullptr;
	//ワールド変換データ
	WorldTransform worldTransform_;

	// 当たり判定 平面
	Plane plane;
	// 当たり判定 レイ
	Ray ray;

	// マウスの座標
	POINT po;
	// マウスのワールド座標
	Vector3 worldPo;
	// W除算をしたマウスのワールド座標
	Vector3 DivWorldPo;
	// マウスまでのベクトル
	Vector3 vecPo;
	// 正規化したマウスのベクトルを入れる変数
	Vector3 norVecPo;
	// クリックフラグ
	bool mouseClick_;
};