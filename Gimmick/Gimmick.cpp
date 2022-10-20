#include "Gimmick.h"
#include "Player.h"

Gimmick::Gimmick() {}

Gimmick::~Gimmick() { delete modelSpring_; }

//初期化
void Gimmick::Initialize() {
	//バネ初期化
	InitializeSpring();
}

void Gimmick::InitializeSpring() {
	//バネのモデル
	modelSpring_ = Model::Create();

	worldTransformSpring_.translation_ = {25.0f, -15.0f, 0.0f};
	worldTransformSpring_.Initialize();
}

//更新
void Gimmick::Update() {
	//乱数シード生成
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//水流座標の範囲
	std::uniform_real_distribution<float> waterFlowDistX(-30.0f, -10.0f);

	//死亡フラグが立った水流の削除
	waterFlow_.remove_if(
	  [](std::unique_ptr<WaterFlow>& waterFlow) { return waterFlow->IsActive(); });

	//水流の速度
	const float kWaterFlowSpeed = 0.5f;
	Vector3 position;
	Vector3 velocity;

	//初期位置
	position = {waterFlowDistX(engine), -20.0f, 0.0f};
	//スピード
	velocity = {0.0f, kWaterFlowSpeed, 0.0f};

	//弾を生成し初期化
	std::unique_ptr<WaterFlow> newWaterFlow = std::make_unique<WaterFlow>();
	newWaterFlow->Initialize(position, velocity);

	//弾を登録
	waterFlow_.push_back(std::move(newWaterFlow));

	//水流更新
	for (std::unique_ptr<WaterFlow>& waterFlow : waterFlow_) {
		waterFlow->Update();
	}
	//ワールド行列更新
	worldTransformSpring_.Update(worldTransformSpring_);
}

//描画
void Gimmick::Draw(ViewProjection& viewProjection) {
	//バネ
	DrawSpring(viewProjection);
	//水流
	for (std::unique_ptr<WaterFlow>& waterFlow : waterFlow_) {
		waterFlow->Draw(viewProjection);
	}
}

void Gimmick::DrawSpring(ViewProjection& viewProjection) {

	modelSpring_->Draw(worldTransformSpring_, viewProjection);
}

Vector3 Gimmick::GetWorldPositionSpring() {
	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransformSpring_.translation_.x;
	worldPos.y = worldTransformSpring_.translation_.y;
	worldPos.z = worldTransformSpring_.translation_.z;

	return worldPos;
}

void Gimmick::OnCollisionSpring(){};
