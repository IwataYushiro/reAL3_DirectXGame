#pragma once
#include "Input.h"
#include "DebugText.h"
#include "CollisionPrimitive.h"
#include "Collision.h"
#include <DirectXMath.h>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <ViewProjection.h>

class Mouse
{
public:
	void Initialize(ViewProjection& viewProjection);

	void Update();
private:
	//インプット
	Input* input_ = nullptr;
	//デバッグテキスト
	DebugText* debugText_ = nullptr;

	// 当たり判定 平面
	Plane plane;
	// 当たり判定 レイ
	Ray ray;

	// マウスの座標
	POINT po;
	// クリックフラグ
	bool mouseClick_;
};