#include "RailCamera.h"

void RailCamera::Initialize(WorldTransform& worldTransform) {
	//ワールドトランスフォームの初期設定
	worldTransform_ = worldTransform;
	
	//ビュープロジェクション初期化

	this->viewProjection_.Initialize();
	//デバックテキスト
	debugText_ = DebugText::GetInstance();
}
//リセット
void RailCamera::Reset() { 
	worldTransform_.translation_ = MyMathUtility::MySetVector3Zero(); 
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();
}
  //更新
void RailCamera::Update() {
	Vector3 velocity = {0.0f, 0.0f, 0.02f};
	Vector3 angle = {0.0f, MyMathUtility::GetRadian(cameraAngle.y), 0.0f};

	cameraAngle.y += 0.1f;
	worldTransform_.rotation_ = angle;
	//行列の再計算
	worldTransform_.Update(worldTransform_);

	viewProjection_.eye = worldTransform_.translation_;
	//ワールド前方ベクトル
	Vector3 forward(0.0f, 0.0f, 1.0f);
	//レールカメラの回転を反映
	forward = worldTransform_.rotation_;
	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_.target = viewProjection_.eye += forward;
	//ワールド上方向ベクトル
	Vector3 up(0.0f, 1.0f, 0.0f);
	//レールカメラの回転を反映
	viewProjection_.up = worldTransform_.rotation_ += up;
	//ビュープロジェクションを更新
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

//描画
void RailCamera::Draw() {}
