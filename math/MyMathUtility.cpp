#include "MyMathUtility.h"
#include <math.h>

//零ベクトルを返す
const Vector3 MyMathUtility::MyVector3Zero() {
	Vector3 v = {0.0f, 0.0f, 0.0f};

	return v;
}
//度を求める
float MyMathUtility::GetDegree(float r) {
	r = (r * 180) / MyMathUtility::PI;

	return r;
}
//ラジアンを求める
float MyMathUtility::GetRadian(float d) {
	d = d * MyMathUtility::PI / 180;

	return d;
}
// 単位行列を求める
Matrix4 MyMathUtility::MyMatrix4Identity() {
	Matrix4 m = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	             0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	return m;
}

// 拡大縮小行列の作成
Matrix4 MyMathUtility::MyMatrix4Scaling(Vector3 scale) {

	//スケーリング行列を宣言
	Matrix4 matScale = MyMathUtility::MyMatrix4Identity();

	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;

	return matScale;
}
// 回転行列の作成
Matrix4 MyMathUtility::MyMatrix4RotationX(float angle) {

	//各軸用回転行列を宣言
	Matrix4 matRotX = MyMathUtility::MyMatrix4Identity();

	matRotX.m[1][1] = cos(angle);
	matRotX.m[1][2] = sin(angle);
	matRotX.m[2][1] = -sin(angle);
	matRotX.m[2][2] = cos(angle);

	return matRotX;
}

Matrix4 MyMathUtility::MyMatrix4RotationY(float angle) {
	//各軸用回転行列を宣言
	Matrix4 matRotY = MyMathUtility::MyMatrix4Identity();

	matRotY.m[0][0] = cos(angle);
	matRotY.m[0][2] = -sin(angle);
	matRotY.m[2][0] = sin(angle);
	matRotY.m[2][2] = cos(angle);

	return matRotY;
}

Matrix4 MyMathUtility::MyMatrix4RotationZ(float angle) {
	//各軸用回転行列を宣言
	Matrix4 matRotZ = MyMathUtility::MyMatrix4Identity();

	matRotZ.m[0][0] = cos(angle);
	matRotZ.m[0][1] = sin(angle);
	matRotZ.m[1][0] = -sin(angle);
	matRotZ.m[1][1] = cos(angle);

	return matRotZ;
}

Matrix4 MyMathUtility::MyMatrix4Rotation(Vector3 rotation) {

	//合成用回転行列を宣言
	Matrix4 matRot = MyMathUtility::MyMatrix4Identity();
	//各軸用回転行列を宣言
	Matrix4 matRotX = MyMathUtility::MyMatrix4RotationX(rotation.x);
	//各軸用回転行列を宣言
	Matrix4 matRotY = MyMathUtility::MyMatrix4RotationY(rotation.y);
	//各軸用回転行列を宣言
	Matrix4 matRotZ = MyMathUtility::MyMatrix4RotationZ(rotation.z);

	//各軸の回転行列を合成
	matRot *= matRotZ *= matRotX *= matRotY; //順番が大事

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

	//合成
	matWorld *= matScale *= matRot *= matTrans;

	return matWorld;
}

//視点移動ベクトルを作成
Vector3 MyMathUtility::MyVector3ViewEye(Input* key) {
	//移動ベクトル
	Vector3 move = MyMathUtility::MyVector3Zero();

	//視点移動の速さ
	const float kEyeSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (key->PushKey(DIK_W)) {
		move.z += kEyeSpeed;
	} else if (key->PushKey(DIK_S)) {
		move.z -= kEyeSpeed;
	}

	return move;
}

//注視点移動ベクトルを作成
Vector3 MyMathUtility::MyVector3ViewTarget(Input* key) {
	//移動ベクトル
	Vector3 move = MyMathUtility::MyVector3Zero();

	//注視点移動の速さ
	const float kTargetSpeed = 0.2f;

	//注視点移動処理
	// //押した方向で移動ベクトルを変更
	if (key->PushKey(DIK_D)) {
		move.x += kTargetSpeed;
		move.x += kTargetSpeed;
	} else if (key->PushKey(DIK_A)) {
		move.x -= kTargetSpeed;
	}

	return move;
}

//上方向ベクトルを作成
Vector3 MyMathUtility::MyVector3ViewUp(Input* key, float& upAngle) {
	//移動ベクトル
	Vector3 move = {cosf(upAngle), sinf(upAngle), 0.0f};

	//上方向の回転速さ[ラジアン/frame]
	const float kUpRotSpeed = 0.05f;

	//上方向回転処理
	if (key->PushKey(DIK_SPACE)) {
		upAngle += kUpRotSpeed;
		// 2πを超えたら元に戻す
		upAngle = fmodf(upAngle, MyMathUtility::PI * 2.0f);
	}

	return move;
}
// FoV変更の処理
float MyMathUtility::MyProjectionFovAngleY(Input* key, float fovY) {
	//視野角変更の速さ
	float speed = 0.03f;
	//上キーで視野角が広がる
	if (key->PushKey(DIK_UP)) {
		fovY += speed;
		if (fovY > MyMathUtility::PI) {
			fovY = MyMathUtility::PI;
		}
	}
	//下キーで視野角が狭まる
	else if (key->PushKey(DIK_DOWN)) {
		fovY -= speed;
		if (fovY < 0.01f) {
			fovY = 0.01f;
		}
	}

	return fovY;
}

// ニアクリップ距離の処理
float MyMathUtility::MyProfectionNearClipZ(Input* key, float nearZ) {
	//ニアクリップ距離の速さ
	float speed = 0.2f;

	// WSキーでニアクリップ距離を増減
	if (key->PushKey(DIK_W)) {
		nearZ += speed;
	} else if (key->PushKey(DIK_S)) {
		nearZ -= speed;
	}

	return nearZ;
}
