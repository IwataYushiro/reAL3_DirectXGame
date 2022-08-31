#include "Player.h"

Player::Player() {}

Player::~Player() {
	//�I�v�V�����̉��
	delete option_;
	delete modelBullet_;
	delete modelOption_;
}

void Player::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	modelBullet_ = Model::CreateFromOBJ("playerbullet", true);
	modelOption_ = Model::CreateFromOBJ("option", true);
	//�I�v�V�����̐���
	option_ = new Option();

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	//�����ŃI�v�V����������
	option_->Initialize(modelOption_, worldTransform_.translation_);
}

void Player::Reset() {
	worldTransform_.translation_ = MyMathUtility::MySetVector3Zero();
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();

	life_ = 5;
	isDead_ = false;
	option_->Reset(worldTransform_.translation_);
	//�e���Z�b�g
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Reset();
	}
}

void Player::Update(ViewProjection& viewprojection) {

	if (!isDead_) {
		//���S�t���O�̗������e���폜
		bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

		//�ړ�����
		Move();
		//���񏈗�
		Rotate();
		//�U������
		Attack();

		//�I�v�V�����̍X�V����
		option_->Update(viewprojection);
		//�e�X�V
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Update();
		}

		//�ړ�����
		MoveLimit();

		worldTransform_.TransferMatrix();
	}
	debugText_->SetScale(1.0f);
	debugText_->SetPos(50, 50);
	debugText_->Printf("life:(%d)", life_);
}

void Player::Draw(ViewProjection& viewProjection) {
	if (!isDead_) {
		model_->Draw(worldTransform_, viewProjection);

		//�e�`��
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Draw(viewProjection);
		}

		//�I�v�V�����`��
		option_->Draw(viewProjection);
	}
}

//�ړ�����
void Player::Move() {

	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 0.3f;

	//�L�[�{�[�h���͂ɂ��ړ�����
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();
	if (input_->PushKey(DIK_A)) {
		move.x = -moveSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x = moveSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.y = moveSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y = -moveSpeed;
	}

	worldTransform_.translation_ += move;
}

//���񏈗�
void Player::Rotate() {

	Vector3 angle = MyMathUtility::MySetVector3Zero();
	float angleSpeed = 0.1f;

	if (input_->PushKey(DIK_Q)) {
		angle.y -= angleSpeed;
	}
	if (input_->PushKey(DIK_E)) {
		angle.y += angleSpeed;
	}

	worldTransform_.rotation_ += angle;
}

//�U������
void Player::Attack() {

	if (input_->IsTriggerMouse(0)) {
		//�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
		//���L�����̍��W���R�s�[
		Vector3 position = worldTransform_.translation_;

		//�e�𐶐���������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelBullet_, position, velocity);

		//�e��o�^
		bullets_.push_back(std::move(newBullet));
		//���郁�����̏��L��������unique_ptr�͂�����������݂ł��Ȃ�
		//���̏��L�������n���邽�߂̋@�\�� std::move()
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
void Player::OnCollision() {
	life_--;
	if (life_ <= 0) {
		isDead_ = true;
	}
}