#pragma once
#include <DirectXMath.h>

/// <summary>
/// 平面
/// </summary>
struct Plane
{
	// 法線ベクトル
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	// 原点(0,0,0)からの距離
	float distance = 0.0f;
};

/// <summary>
/// レイ(半直線)
/// </summary>
struct Ray
{
	// 始点座標
	DirectX::XMVECTOR start = { 0,0,0,0 };
	// 方向
	DirectX::XMVECTOR dir = { 0,1,1,0 };
};