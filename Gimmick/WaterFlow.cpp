#include "WaterFrow.h"

WaterFlow::WaterFlow() {}

WaterFlow::~WaterFlow() { delete model_; }

//����������
void WaterFlow::Initialize() {

	//�����̃��f��
	model_ = Model::CreateFromOBJ("playerbullet", true);

	width_ = 10.0f;  //����
	height_ = 20.0f; //�c��
	speed_ = 0.5f;   //���x

	//���[���h���W������
	worldTransform_.Initialize();

	bright_ = 255;     //���邳
	isActive_ = false; //�����Ă邩
}

void WaterFlow::Update() {
	//�����V�[�h����
	std::random_device seed_gen;
	//�����Z���k�E�c�C�X�^�[
	std::mt19937_64 engine(seed_gen());
	//�������W�͈̔�
	std::uniform_real_distribution<float> waterFlowDistX(-30.0f, -10.0f);

	if (isActive_ == false) {

		isActive_ = true;
		worldTransform_.translation_ = {waterFlowDistX(engine), -20.0f, 0.0f};
	}

	if (isActive_ == true) {
		worldTransform_.translation_.y += speed_;
	}
	if (--deathTimer_ <= 0) {
		isActive_ = false;
	}
}

void WaterFlow::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

Vector3 WaterFlow::GetWorldPosition() {
	//���[���h���W���擾
	Vector3 worldPos;

	
		//���[���h�s��̕��s�ړ��������擾
		worldPos.x = worldTransform_.translation_.x;
		worldPos.y = worldTransform_.translation_.y;
		worldPos.z = worldTransform_.translation_.z;

		return worldPos;
	
}

void WaterFlow::OnCollision(){};