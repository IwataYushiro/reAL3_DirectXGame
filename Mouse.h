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
