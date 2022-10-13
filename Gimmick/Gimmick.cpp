#include "Gimmick.h"
#include "Player.h"

Gimmick::Gimmick() {}

Gimmick::~Gimmick() {
	delete modelSpring_;
	delete modelWaterFlow_;
}

//������
void Gimmick::Initialize() {
	//�o�l������
	InitializeSpring();
	//����������
	InitializeWaterFlow();
}

void Gimmick::InitializeSpring() {
	//�o�l�̃��f��
	modelSpring_ = Model::Create();

	worldTransformSpring_.translation_ = {25.0f, -15.0f, 0.0f};
	worldTransformSpring_.Initialize();
}
//����������
void Gimmick::InitializeWaterFlow() {

	//�����̃��f��
	modelWaterFlow_ = Model::CreateFromOBJ("playerbullet", true);

	waterFlowWidth_ = 10.0f;  //����
	waterFlowHeight_ = 20.0f; //�c��
	waterFlowSpeed_ = 0.5f;   //���x
	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		//���[���h���W������
		worldTransformWaterFlow_[i].Initialize();

		waterFlowBright_[i] = 255;     //���邳
		isActiveWaterFlow_[i] = false; //�����Ă邩
	}
}
//�X�V
void Gimmick::Update() {
	//�����X�V
	UpdateWaterFlow();
	//���[���h�s��X�V
	worldTransformSpring_.Update(worldTransformSpring_);
	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		worldTransformWaterFlow_[i].Update(worldTransformWaterFlow_[i]);
	}
}
void Gimmick::UpdateWaterFlow() {
	//�����V�[�h����
	std::random_device seed_gen;
	//�����Z���k�E�c�C�X�^�[
	std::mt19937_64 engine(seed_gen());
	//�������W�͈̔�
	std::uniform_real_distribution<float> waterFlowDistX(-30.0f, -10.0f);

	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		if (isActiveWaterFlow_[i] == false) {

			isActiveWaterFlow_[i] = true;
			worldTransformWaterFlow_[i].translation_ = {waterFlowDistX(engine), -20.0f, 0.0f};

			if (i % 2 == 0) {
				break;
			}
		}
	}

	for (int i = 0; i < WATERFLOW_MAX_; i++) {

		if (isActiveWaterFlow_[i] == true) {
			worldTransformWaterFlow_[i].translation_.y += waterFlowSpeed_;
		}
		if (worldTransformWaterFlow_[i].translation_.y >= 30.0f) {
			isActiveWaterFlow_[i] = false;
		}
	}
	
}
//�`��
void Gimmick::Draw(ViewProjection& viewProjection) {
	//�o�l
	DrawSpring(viewProjection);
	//����
	DrawWaterFlow(viewProjection);
}

void Gimmick::DrawSpring(ViewProjection& viewProjection) {

	modelSpring_->Draw(worldTransformSpring_, viewProjection);
}

void Gimmick::DrawWaterFlow(ViewProjection& viewProjection) {
	for (int i = 0; i < WATERFLOW_MAX_; i++) {
		if (isActiveWaterFlow_[i] == true) {
			modelWaterFlow_->Draw(worldTransformWaterFlow_[i], viewProjection);
		}
	}
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

Vector3& Gimmick::GetWorldPositionWaterFlow() {
	//���[���h���W���擾
	Vector3 worldPos[WATERFLOW_MAX_];

	for (int i = 0; i < WATERFLOW_MAX_; i++) {

		//���[���h�s��̕��s�ړ��������擾
		worldPos[i].x = worldTransformWaterFlow_[i].translation_.x;
		worldPos[i].y = worldTransformWaterFlow_[i].translation_.y;
		worldPos[i].z = worldTransformWaterFlow_[i].translation_.z;

		return worldPos[i];
	}
}
void Gimmick::OnCollisionSpring(){};
void Gimmick::OnCollisionWaterFlow(){};