#include "Enemy.h"
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
	worldTransform_.translation_ = {1.0f, 1.0f, 30.0f};

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
	//�e�̑��x
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0.1f, kBulletSpeed);

	//�x�N�g���ƍs��Ŋ|���Z
	velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
	//�G�L�����̍��W���R�s�[
	Vector3 position = worldTransform_.translation_;

	//�e�𐶐���������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, position, velocity);

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
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
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