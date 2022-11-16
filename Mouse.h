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
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	// �����蔻�� ����
	Plane plane;
	// �����蔻�� ���C
	Ray ray;

	// �}�E�X�̍��W
	POINT po;
	// �N���b�N�t���O
	bool mouseClick_;
};