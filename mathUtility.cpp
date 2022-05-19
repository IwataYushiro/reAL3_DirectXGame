#include "math/MathUtility.h"

// �P�ʍs������߂�
Matrix4 Matrix4::Matrix4Identity() { 
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;

	return m;
} 
// �]�u�s������߂�
Matrix4 Matrix4::Matrix4Transpose(const Matrix4& m) 
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = m[j][i];
		}
	}
	return m;
}