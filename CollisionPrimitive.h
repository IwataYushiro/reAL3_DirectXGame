#pragma once
#include <DirectXMath.h>

/// <summary>
/// ����
/// </summary>
struct Plane
{
	// �@���x�N�g��
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	// ���_(0,0,0)����̋���
	float distance = 0.0f;
};

/// <summary>
/// ���C(������)
/// </summary>
struct Ray
{
	// �n�_���W
	DirectX::XMVECTOR start = { 0,0,0,0 };
	// ����
	DirectX::XMVECTOR dir = { 0,1,1,0 };
};