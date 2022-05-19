#include "math/MathUtility.h"

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