#include "MyMathUtility.h"
#include <math.h>

namespace MyMathUtility {

// �P�ʍs������߂�
Matrix4 MyMathUtility::MyMatrix4Identity() {
	Matrix4 m = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
	};
	return m;
}

// �g��k���s��̍쐬
Matrix4 MyMathUtility::MyMatrix4Scaling(float sx, float sy, float sz) {

	//�X�P�[�����O�s���錾
	Matrix4 matScale = MyMathUtility::MyMatrix4Identity();

	matScale.m[0][0] = sx;
	matScale.m[1][1] = sy;
	matScale.m[2][2] = sz;

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
Matrix4 MyMathUtility::MyMatrix4Rotation(float ax, float ay, float az) {

	//�����p��]�s���錾
	Matrix4 matRot = MyMathUtility::MyMatrix4Identity();
	//�e���p��]�s���錾
	Matrix4 matRotX = MyMathUtility::MyMatrix4RotationX(ax);
	//�e���p��]�s���錾
	Matrix4 matRotY = MyMathUtility::MyMatrix4RotationY(ay);
	//�e���p��]�s���錾
	Matrix4 matRotZ = MyMathUtility::MyMatrix4RotationZ(az);

	//�e���̉�]�s�������
	matRot *= matRotZ *= matRotX *= matRotY; //���Ԃ��厖

	return matRot;
}
  // ���s�ړ��s��̍쐬
Matrix4 MyMathUtility::MyMatrix4Translation(float tx, float ty, float tz) {

}
Matrix4 MyMathUtility::MyMatrix4WorldTransform(
  const Vector3& scale, const Vector3& rotation, const Vector3& transform) {}

} // namespace MyMathUtility