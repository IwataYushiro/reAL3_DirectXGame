#include "Player.h"

Player::Player() {}

Player::~Player() {
	delete gimmick_;
	//�I�v�V�����̉��
	delete modelDead_;
}

void Player::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	modelDead_ = Model::CreateFromOBJ("playerdead", true);

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, -10.0f, 0.0f};
	//����������
	gimmick_ = new Gimmick();

	isSwim = true;
	gravity = -0.6f;
}

void Player::Reset() {
	worldTransform_.translation_ = {0.0f, -10.0f, 0.0f};
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();

	life_ = 5;
	isDead_ = false;
}
//�Q�[���I�[�o�[���W
void Player::Death() {}

void Player::Update(ViewProjection& viewprojection) {

	if (!isDead_) {

		//�ړ�����
		Move();
		//�W�����v����
		Jump();
		//�ړ�����
		MoveLimit();
	}

	worldTransform_.TransferMatrix();
	debugText_->SetScale(1.0f);
	debugText_->SetPos(50, 50);
	debugText_->Printf("life:(%d)", life_);
}

void Player::Draw(ViewProjection& viewProjection) {
	if (!isDead_) {
		model_->Draw(worldTransform_, viewProjection);
	}
}

void Player::DrawDead(ViewProjection& viewProjection) {
	modelDead_->Draw(worldTransform_, viewProjection);
}
//�ړ�����
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

void Player::Jump() {
	//�X�y�[�X�L�[���������u�ԉj��(�����痣��Ă�����)
	if (input_->TriggerKey(DIK_SPACE)) {
		isSwim = true;
		//�d�͂�0�ɂȂ�
		gravity = 0.0f;
	}
	//�j���ł����
	if (isSwim == true) {
		//�v���C���[�̍��W -= ����(�Œ�) - �d��(���X�ɏオ��)�@
		worldTransform_.translation_.y -= buoyancy - gravity;
		//�d�͂͏��X�ɏオ��
		gravity -= 0.02f;
	}
	if (gravity <= -1.0f) {
		gravity = -1.0f;
	}
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

//���[���h���W���擾
Vector3 Player::GetWorldPosition() {

	//���[���h���W���擾
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
void Player::OnCollisionSpring() {
	isSwim = true;
	//�d�͂�0�ɂȂ�
	gravity = 0.5f;
}
void Player::OnCollisionWaterFlow() {
	isSwim = true;
	worldTransform_.translation_.y += gimmick_->GetWaterFlowSpeed();
	gravity = 0.2f;
}