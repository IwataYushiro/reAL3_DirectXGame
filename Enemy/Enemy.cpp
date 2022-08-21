#include "Enemy.h"
#include "Player.h"
// ������
void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("texture/enemy.png");
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.translation_ = {1.0f, 1.0f, 80.0f};

	//�����t�F�[�Y
	phase_ = Phase::Approach;
	//�ڋ߃t�F�[�Y������
	InitializeApproach();
}
// �ڋ߃t�F�[�Y������
void Enemy::InitializeApproach() {
	//���˃^�C�}�[������
	fireTimer = kFireInterval;
}

//�X�V
void Enemy::Update() {

	//���S�t���O�̗������e���폜
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });

	//���W���ړ�������
	switch (phase_) {
	case Enemy::Phase::Approach:

		UpdateApproach();
		break;

	case Enemy::Phase::Attack:

		UpdateAttack();
		break;

	case Enemy::Phase::Leave:
		UpdateLeave();
		break;
	}
	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Update();
	}

	//�s��X�V
	worldTransform_.Update(worldTransform_);
}

//�e����
void Enemy::Fire() {

	assert(player_);

	//�e�̑��x
	const float kBulletSpeed = -1.0f;
	Vector3 velocity;

	//���@�̃��[���h���W���擾
	player_->GetWorldPosition();
	//�G�̃��[���h���W���擾
	GetWorldPosition();
	//�G�����@�̍����x�N�g�������߂�
	velocity = player_->GetWorldPosition() -= GetWorldPosition();
	// �x�N�g���̐��K��
	MyMathUtility::MyVector3Normalize(velocity);
	// �x�N�g���̒����𑬂��ɍ��킹��
	velocity.z = kBulletSpeed;

	////�x�N�g���ƍs��Ŋ|���Z
	// velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
	////�G�L�����̍��W���R�s�[
	// Vector3 position = worldTransform_.translation_;

	//�e�𐶐���������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//�e��o�^
	enemyBullets_.push_back(std::move(newBullet));
}

//�`��
void Enemy::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Draw(viewProjection);
	}
}

//��ԕω��p�̍X�V�֐�
//�ڋ�
void Enemy::UpdateApproach() {
	//���x
	Vector3 velocity;

	//�ړ�
	velocity = {0.0f, 0.0f, -0.1f};
	worldTransform_.translation_ += velocity;

	//���˃^�C�}�[�J�E���g�_�E��
	fireTimer--;
	//�w�莞�ԂɒB����
	if (fireTimer <= 0) {
		//�e����
		Fire();
		//���˃^�C�}�[������
		fireTimer = kFireInterval;
	}

	//�w��̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z < 50.0f) {
		phase_ = Phase::Attack;
	}
}
//�U��
void Enemy::UpdateAttack() {

	//���x
	Vector3 velocity;

	//�ړ�
	velocity = {0.1f, 0.0f, 0.0f};
	worldTransform_.translation_ += velocity;

	//�w��̈ʒu�ɓ��B�����獶��
	if (worldTransform_.translation_.x >= 30.0f) {
		worldTransform_.translation_.x = -worldTransform_.translation_.x;

	}
	/*if (worldTransform_.translation_.x >= 30.0f ) {
		velocity.x = velocity.x * -1.0f;
	}*/

	
	
	
	//���˃^�C�}�[�J�E���g�_�E��
	fireTimer--;
	//�w�莞�ԂɒB����
	if (fireTimer <= 0) {
		//�e����
		Fire();
		//���˃^�C�}�[������
		fireTimer = kFireInterval;
	}

}

//���E
void Enemy::UpdateLeave() {
	//���x
	Vector3 velocity;

	//�ړ�
	velocity = {0.1f, 0.1f, 0.0f};
	worldTransform_.translation_ += velocity;
}

//���[���h���W���擾
Vector3 Enemy::GetWorldPosition() {

	//���[���h���W���擾
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
void Enemy::OnCollision() {}