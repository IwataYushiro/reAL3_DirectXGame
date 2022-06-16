#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}
void Player::Update() {
	Vector3 move = {0.0f, 0.0f, 0.0f};
	float speed = 0.1f;

	Matrix4 matTrans = MathUtility::Matrix4Identity();

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= speed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += speed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += speed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= speed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	matTrans = MathUtility::Matrix4Translation(
	  worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransform_.matWorld_.operator*=(matTrans);

	worldTransform_.TransferMatrix();

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "move:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
