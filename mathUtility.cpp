#include "math/MathUtility.h"
#include <math.h>

// 単位行列を求める
Matrix4 Matrix4::Matrix4Identity() { 
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;

	return m;
} 
// 転置行列を求める
Matrix4 Matrix4::Matrix4Transpose(const Matrix4& m) 
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = m[j][i];
		}
	}
	return m;
}
// 拡大縮小行列の作成
Matrix4 Matrix4::Matrix4Scaling(float sx, float sy, float sz)
{ 
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	m[3][3] = 1.0f;

	return m;
}

// 回転行列の作成
Matrix4 Matrix4::Matrix4RotationX(float angle) {
	m[0][0] = 1.0f;
	m[1][1] = cos(angle);
	m[1][2] = sin(angle);
	m[2][1] = -sin(angle);
	m[2][2] = cos(angle);
	m[3][3] = 1.0f;

	return m;
}
Matrix4 Matrix4::Matrix4RotationY(float angle) {
	m[0][0] = cos(angle);
	m[0][2] = -sin(angle);
	m[1][1] = 1.0f;
	m[2][0] = sin(angle);
	m[2][2] = cos(angle);
	m[3][3] = 1.0f;
	
	return m;
}
Matrix4 Matrix4::Matrix4RotationZ(float angle) {
	m[0][0] = cos(angle);
	m[0][1] = sin(angle);
	m[1][0] = -sin(angle);
	m[1][1] = cos(angle);
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;

	return m;
}

// 平行移動行列の作成
Matrix4 Matrix4::Matrix4Translation(float tx, float ty, float tz) {

	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][0] = tx;
	m[3][1] = ty;
	m[3][2] = tz;
	m[3][3] = 1.0f;

	return m;
}


