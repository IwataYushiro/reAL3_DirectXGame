#include "MyMathUtility.h"
#include <math.h>

//��x�N�g����Ԃ�
const Vector3 MyMathUtility::MyVector3Zero() {
	Vector3 v = {0.0f, 0.0f, 0.0f};

	return v;
}
//�x�����߂�
float MyMathUtility::GetDegree(float r) {
	r = (r * 180) / MyMathUtility::PI;

	return r;
}
//���W�A�������߂�
float MyMathUtility::GetRadian(float d) {
	d = d * MyMathUtility::PI / 180;

	return d;
}
// �P�ʍs������߂�
Matrix4 MyMathUtility::MyMatrix4Identity() {
	Matrix4 m = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	             0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return m;
}

// �g��k���s��̍쐬
Matrix4 MyMathUtility::MyMatrix4Scaling(Vector3 scale) {

	//�X�P�[�����O�s���錾
	Matrix4 matScale = MyMathUtility::MyMatrix4Identity();

	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;

	return matScale;
}
// ��]�s��̍쐬
Matrix4 MyMathUtility::MyMatrix4RotationX(float angle) {

	//�e���p��]�s���錾
	Matrix4 matRotX = MyMathUtility::MyMatrix4Identity();

	matRotX.m[1][1] = cos(angle);
	matRotX.m[1][2] = sin(angle);
	matRotX.m[2][1] = -sin(angle);
	matRotX.m[2][2] = cos(angle);

	return matRotX;
}

Matrix4 MyMathUtility::MyMatrix4RotationY(float angle) {
	//�e���p��]�s���錾
	Matrix4 matRotY = MyMathUtility::MyMatrix4Identity();

	matRotY.m[0][0] = cos(angle);
	matRotY.m[0][2] = -sin(angle);
	matRotY.m[2][0] = sin(angle);
	matRotY.m[2][2] = cos(angle);

	return matRotY;
}

Matrix4 MyMathUtility::MyMatrix4RotationZ(float angle) {
	//�e���p��]�s���錾
	Matrix4 matRotZ = MyMathUtility::MyMatrix4Identity();

	matRotZ.m[0][0] = cos(angle);
	matRotZ.m[0][1] = sin(angle);
	matRotZ.m[1][0] = -sin(angle);
	matRotZ.m[1][1] = cos(angle);

	return matRotZ;
}

Matrix4 MyMathUtility::MyMatrix4Rotation(Vector3 rotation) {

	//�����p��]�s���錾
	Matrix4 matRot = MyMathUtility::MyMatrix4Identity();
	//�e���p��]�s���錾
	Matrix4 matRotX = MyMathUtility::MyMatrix4RotationX(rotation.x);
	//�e���p��]�s���錾
	Matrix4 matRotY = MyMathUtility::MyMatrix4RotationY(rotation.y);
	//�e���p��]�s���錾
	Matrix4 matRotZ = MyMathUtility::MyMatrix4RotationZ(rotation.z);

	//�e���̉�]�s�������
	matRot *= matRotZ *= matRotX *= matRotY; //���Ԃ��厖

	return matRot;
}

Matrix4 MyMathUtility::MyMatrix4Translation(Vector3 translation) {
	Matrix4 matTrans = MyMathUtility::MyMatrix4Identity();

	matTrans.m[3][0] = translation.x;
	matTrans.m[3][1] = translation.y;
	matTrans.m[3][2] = translation.z;

	return matTrans;
}

Matrix4 MyMathUtility::MyMatrix4WorldTransform(WorldTransform worldTransform) {
	Matrix4 matWorld = MyMathUtility::MyMatrix4Identity();

	Matrix4 matScale = MyMathUtility::MyMatrix4Scaling(worldTransform.scale_);

	Matrix4 matRot = MyMathUtility::MyMatrix4Rotation(worldTransform.rotation_);

	Matrix4 matTrans = MyMathUtility::MyMatrix4Translation(worldTransform.translation_);

	//����
	matWorld *= matScale *= matRot *= matTrans;

	return matWorld;
}

//���_�ړ��x�N�g�����쐬
Vector3 MyMathUtility::MyVector3ViewEye(Input* key) {
	//�ړ��x�N�g��
	Vector3 move = MyMathUtility::MyVector3Zero();

	//���_�ړ��̑���
	const float kEyeSpeed = 0.2f;

	//�����������ňړ��x�N�g����ύX
	if (key->PushKey(DIK_W)) {
		move.z += kEyeSpeed;
	} else if (key->PushKey(DIK_S)) {
		move.z -= kEyeSpeed;
	}

	return move;
}

//�����_�ړ��x�N�g�����쐬
Vector3 MyMathUtility::MyVector3ViewTarget(Input* key) {
	//�ړ��x�N�g��
	Vector3 move = MyMathUtility::MyVector3Zero();

	//�����_�ړ��̑���
	const float kTargetSpeed = 0.2f;

	//�����_�ړ�����
	// //�����������ňړ��x�N�g����ύX
	if (key->PushKey(DIK_D)) {
		move.x += kTargetSpeed;
		move.x += kTargetSpeed;
	} else if (key->PushKey(DIK_A)) {
		move.x -= kTargetSpeed;
	}

	return move;
}

//������x�N�g�����쐬
Vector3 MyMathUtility::MyVector3ViewUp(Input* key, float& upAngle) {
	//�ړ��x�N�g��
	Vector3 move = {cosf(upAngle), sinf(upAngle), 0.0f};

	//������̉�]����[���W�A��/frame]
	const float kUpRotSpeed = 0.05f;

	//�������]����
	if (key->PushKey(DIK_SPACE)) {
		upAngle += kUpRotSpeed;
		// 2�΂𒴂����猳�ɖ߂�
		upAngle = fmodf(upAngle, MyMathUtility::PI * 2.0f);
	}

	return move;
}
// FoV�ύX�̏���
float MyMathUtility::MyProjectionFovAngleY(Input* key, float fovY) {
	//����p�ύX�̑���
	float speed = 0.03f;
	//��L�[�Ŏ���p���L����
	if (key->PushKey(DIK_UP)) {
		fovY += speed;
		if (fovY > MyMathUtility::PI) {
			fovY = MyMathUtility::PI;
		}
	}
	//���L�[�Ŏ���p�����܂�
	else if (key->PushKey(DIK_DOWN)) {
		fovY -= speed;
		if (fovY < 0.01f) {
			fovY = 0.01f;
		}
	}

	return fovY;
}

// �j�A�N���b�v�����̏���
float MyMathUtility::MyProfectionNearClipZ(Input* key, float nearZ) {
	//�j�A�N���b�v�����̑���
	float speed = 0.2f;

	// WS�L�[�Ńj�A�N���b�v�����𑝌�
	if (key->PushKey(DIK_W)) {
		nearZ += speed;
	} else if (key->PushKey(DIK_S)) {
		nearZ -= speed;
	}

	return nearZ;
}
