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

	//�ړ�����
	Move();
	//���񏈗�
	Rotate();
	//�ړ�����
	MoveLimit();

	worldTransform_.TransferMatrix();

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "move:( %f , %f , %f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Move() {

	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 0.3f;

	//�L�[�{�[�h���͂ɂ��ړ�����
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();
	if (input_->PushKey(DIK_LEFT)) {
		move.x = -moveSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x = moveSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y = moveSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y = -moveSpeed;
	}

	worldTransform_.translation_ += move;
}

void Player::Rotate() {

	Vector3 angle = MyMathUtility::MySetVector3Zero();
	float angleSpeed = 0.1f;

	if (input_->PushKey(DIK_A)) {
		angle.y -= angleSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		angle.y += angleSpeed;
	}

	worldTransform_.rotation_ += angle;
}
void Player::MoveLimit() {
	//�ړ����E���W
	const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 18.0f;
	//�͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	//�s��X�V
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
}
