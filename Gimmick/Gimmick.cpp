#include "Gimmick.h"
#include "Player.h"

Gimmick::Gimmick() {}

Gimmick::~Gimmick() { delete modelSpring_; }

//������
void Gimmick::Initialize() {
	//�o�l������
	InitializeSpring();
}

void Gimmick::InitializeSpring() {
	//�o�l�̃��f��
	modelSpring_ = Model::Create();

	worldTransformSpring_.translation_ = {25.0f, -15.0f, 0.0f};
	worldTransformSpring_.Initialize();
}

//�X�V
void Gimmick::Update() {
	//�����V�[�h����
	std::random_device seed_gen;
	//�����Z���k�E�c�C�X�^�[
	std::mt19937_64 engine(seed_gen());
	//�������W�͈̔�
	std::uniform_real_distribution<float> waterFlowDistX(-30.0f, -10.0f);

	//���S�t���O�������������̍폜
	waterFlow_.remove_if(
	  [](std::unique_ptr<WaterFlow>& waterFlow) { return waterFlow->IsActive(); });

	//�����̑��x
	const float kWaterFlowSpeed = 0.5f;
	Vector3 position;
	Vector3 velocity;

	//�����ʒu
	position = {waterFlowDistX(engine), -20.0f, 0.0f};
	//�X�s�[�h
	velocity = {0.0f, kWaterFlowSpeed, 0.0f};

	//�e�𐶐���������
	std::unique_ptr<WaterFlow> newWaterFlow = std::make_unique<WaterFlow>();
	newWaterFlow->Initialize(position, velocity);

	//�e��o�^
	waterFlow_.push_back(std::move(newWaterFlow));

	//�����X�V
	for (std::unique_ptr<WaterFlow>& waterFlow : waterFlow_) {
		waterFlow->Update();
	}
	//���[���h�s��X�V
	worldTransformSpring_.Update(worldTransformSpring_);
}

//�`��
void Gimmick::Draw(ViewProjection& viewProjection) {
	//�o�l
	DrawSpring(viewProjection);
	//����
	for (std::unique_ptr<WaterFlow>& waterFlow : waterFlow_) {
		waterFlow->Draw(viewProjection);
	}
}

void Gimmick::DrawSpring(ViewProjection& viewProjection) {

	modelSpring_->Draw(worldTransformSpring_, viewProjection);
}

Vector3 Gimmick::GetWorldPositionSpring() {
	//���[���h���W���擾
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransformSpring_.translation_.x;
	worldPos.y = worldTransformSpring_.translation_.y;
	worldPos.z = worldTransformSpring_.translation_.z;

	return worldPos;
}

void Gimmick::OnCollisionSpring(){};
