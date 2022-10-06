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
	
	worldTransformSpring_.Initialize();
	worldTransformSpring_.translation_ = {25.0f, -15.0f, 0.0f};
}

//�X�V
void Gimmick::Update() { 


	//���[���h�s��X�V
	worldTransformSpring_.Update(worldTransformSpring_); 
}

//�`��
void Gimmick::Draw(ViewProjection& viewProjection) {
	//�o�l
	DrawSpring(viewProjection);
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