#pragma once
#include "Input.h"
#include "DebugText.h"
#include "CollisionPrimitive.h"
#include <windows.h>

class Mouse
{
public:
	void Initialize();

	void Update();

	void Draw();
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
