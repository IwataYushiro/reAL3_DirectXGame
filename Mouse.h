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
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	// ���f��
	Model* model_ = nullptr;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// �����蔻�� ����
	Plane plane;
	// �����蔻�� ���C
	Ray ray;

	// �}�E�X�̍��W
	POINT po;
	// �}�E�X�̃��[���h���W
	Vector3 worldPo;
	// W���Z�������}�E�X�̃��[���h���W
	Vector3 DivWorldPo;
	// �}�E�X�܂ł̃x�N�g��
	Vector3 vecPo;
	// ���K�������}�E�X�̃x�N�g��������ϐ�
	Vector3 norVecPo;
	// �N���b�N�t���O
	bool mouseClick_;
};