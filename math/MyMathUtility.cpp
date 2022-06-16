#include "MyMathUtility.h"
#include <math.h>

// 単位行列を求める
Matrix4 MyMathUtility::MySetMatrix4Identity() {
	Matrix4 m = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	             0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return m;
}

// 拡大縮小行列の作成
Matrix4 MyMathUtility::MyGenMatrix4Scaling(Vector3 scale) {

	//スケーリング行列を宣言
	Matrix4 matScale = MyMathUtility::MySetMatrix4Identity();

	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;

	return matScale;
}
// 回転行列の作成
Matrix4 MyMathUtility::MyGenMatrix4RotationX(float angle) {

	//各軸用回転行列を宣言
	Matrix4 matRotX = MyMathUtility::MySetMatrix4Identity();

	matRotX.m[1][1] = cos(angle);
	matRotX.m[1][2] = sin(angle);
	matRotX.m[2][1] = -sin(angle);
	matRotX.m[2][2] = cos(angle);

	return matRotX;
}

Matrix4 MyMathUtility::MyGenMatrix4RotationY(float angle) {
	//各軸用回転行列を宣言
	Matrix4 matRotY = MyMathUtility::MySetMatrix4Identity();

	matRotY.m[0][0] = cos(angle);
	matRotY.m[0][2] = -sin(angle);
	matRotY.m[2][0] = sin(angle);
	matRotY.m[2][2] = cos(angle);

	return matRotY;
}

Matrix4 MyMathUtility::MyGenMatrix4RotationZ(float angle) {
	//各軸用回転行列を宣言
	Matrix4 matRotZ = MyMathUtility::MySetMatrix4Identity();

	matRotZ.m[0][0] = cos(angle);
	matRotZ.m[0][1] = sin(angle);
	matRotZ.m[1][0] = -sin(angle);
	matRotZ.m[1][1] = cos(angle);

	return matRotZ;
}

Matrix4 MyMathUtility::MySynMatrix4Rotation(Vector3 rotation) {

	//合成用回転行列を宣言
	Matrix4 matRot = MyMathUtility::MySetMatrix4Identity();
	//各軸用回転行列を宣言
	Matrix4 matRotX = MyMathUtility::MyGenMatrix4RotationX(rotation.x);
	//各軸用回転行列を宣言
	Matrix4 matRotY = MyMathUtility::MyGenMatrix4RotationY(rotation.y);
	//各軸用回転行列を宣言
	Matrix4 matRotZ = MyMathUtility::MyGenMatrix4RotationZ(rotation.z);

	//各軸の回転行列を合成
	matRot *= matRotZ *= matRotX *= matRotY; //順番が大事

	return matRot;
}

Matrix4 MyMathUtility::MyGenMatrix4Translation(Vector3 translation) {
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();

	matTrans.m[3][0] = translation.x;
	matTrans.m[3][1] = translation.y;
	matTrans.m[3][2] = translation.z;

	return matTrans;
}

Matrix4 MyMathUtility::MySynMatrix4WorldTransform(WorldTransform worldTransform) {
	Matrix4 matWorld = MyMathUtility::MySetMatrix4Identity();

	Matrix4 matScale = MyMathUtility::MyGenMatrix4Scaling(worldTransform.scale_);

	Matrix4 matRot = MyMathUtility::MySynMatrix4Rotation(worldTransform.rotation_);
	
	Matrix4 matTrans = MyMathUtility::MyGenMatrix4Translation(worldTransform.translation_);
	
	//合成
	matWorld*= matScale *= matRot *= matTrans;

	return matWorld;
}

