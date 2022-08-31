#include "Enemy.h"
#include "GameScene.h"
#include "Player.h"
// ������
Enemy::~Enemy() {
	delete modelBullet_;
	delete modelDead_;
}

void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	modelBullet_ = Model::CreateFromOBJ("enemybullet", true);
	modelDead_ = Model::CreateFromOBJ("enemy1dead", true);

	//�V���O���g���C���X�^���X���擾
	debugText_ = DebugText::GetInstance();

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	//�����X�e�[�W
	Stage1Parameter();
}

// �ڋ߃t�F�[�Y������
void Enemy::InitializeApproach() {
	//���˃^�C�}�[������
	fireTimer = kFireInterval;
}

//�p�����[�^
void Enemy::Stage1Parameter() {
	worldTransform_.translation_ = {1.0f, 1.0f, 80.0f};
	//�����t�F�[�Y
	phase_ = Phase::ApproachStage1;
	InitializeApproach();

	life_ = 20;
	isDead_ = false;
	//�e���Z�b�g
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Reset();
	}
}

void Enemy::Stage2Parameter() {
	worldTransform_.translation_ = {5.0f, 5.0f, 100.0f};
	//�����t�F�[�Y
	phase_ = Phase::ApproachStage2;
	InitializeApproach();

	life_ = 40;
	isDead_ = false;
	//�e���Z�b�g
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Reset();
	}
}

//���Z�b�g
void Enemy::Reset() { Stage1Parameter(); }

//�X�V
void Enemy::Update() {

	if (!isDead_) {
		//���S�t���O�̗������e���폜
		enemyBullets_.remove_if(
		  [](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });

		//���W���ړ�������
		switch (phase_) {
		case Enemy::Phase::ApproachStage1:

			UpdateApproachStage1();
			break;

		case Enemy::Phase::AttackStage1:

			UpdateAttackStage1();
			break;
			//�X�e�[�W2
		case Enemy::Phase::ApproachStage2:

			UpdateApproachStage2();
			break;

		case Enemy::Phase::AttackStage2:

			UpdateAttackStage2();
			break;
		}
		//�e�X�V
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Update();
		}
		//���C�t�\��
		debugText_->SetScale(1.0f);
		debugText_->SetPos(50, 100);
		debugText_->Printf("enemy life:(%d)", life_);
	} else {
		//���W���ړ�������
		switch (phase_) {
		case Enemy::Phase::Leave:
			UpdateLeave();
			break;
		}
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
	newBullet->Initialize(modelBullet_, worldTransform_.translation_, velocity);

	//�e��o�^
	enemyBullets_.push_back(std::move(newBullet));
}

//�`��
void Enemy::DrawStage1(const ViewProjection& viewProjection) {
	if (!isDead_) {
		//���f���̕`��
		model_->Draw(worldTransform_, viewProjection);

		//�e�`��
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(viewProjection);
		}
	} else {
		//���f���̕`��
		modelDead_->Draw(worldTransform_, viewProjection);
	}
}

void Enemy::DrawStage2(const ViewProjection& viewProjection) {
	if (!isDead_) {
		//���f���̕`��
		model_->Draw(worldTransform_, viewProjection);

		//�e�`��
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(viewProjection);
		}
	} else {
		//���f���̕`��
		modelDead_->Draw(worldTransform_, viewProjection);
	}
}

//��ԕω��p�̍X�V�֐�
//�ڋ�
void Enemy::UpdateApproachStage1() {
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
		phase_ = Phase::AttackStage1;
	}
}
void Enemy::UpdateApproachStage2() {
	//���x
	Vector3 velocity;
	//�ړ�
	velocity = {0.0f, 0.0f, -0.3f};
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
	if (worldTransform_.translation_.z < 70.0f) {
		phase_ = Phase::AttackStage2;
	}
}

//�U��
void Enemy::UpdateAttackStage1() {

	//���x
	Vector3 velocity;
		//�ړ�
		velocity = {0.1f, 0.0f, 0.0f};
		if (isReverse_) {
			worldTransform_.translation_ -= velocity;
		} else {
			worldTransform_.translation_ += velocity;
		}

		//�w��̈ʒu�ɓ��B�����甽�]
		if (worldTransform_.translation_.x >= 30.0f) {
			isReverse_ = true;
		}
		if (worldTransform_.translation_.x <= -30.0f) {
			isReverse_ = false;
		}

		//���˃^�C�}�[�J�E���g�_�E��
		fireTimer--;
		//�w�莞�ԂɒB����
		if (fireTimer <= 0) {
			//�e����
			Fire();
			//���˃^�C�}�[������
			fireTimer = kFireInterval;
		}
		//���񂾂�
		if (life_ <= 0) {
			phase_ = Phase::Leave;
			life_ = 0;
			isDead_ = true;
		}
}

void Enemy::UpdateAttackStage2() {

	//���x
	Vector3 velocity;
	
	//�ړ�
	velocity = {0.2f, 0.2f, -0.1f};
	if (isReverse_) {
		worldTransform_.translation_ -= velocity;
	} else {
		worldTransform_.translation_ += velocity;
	}

	//�w��̈ʒu�ɓ��B�����甽�]
	if (worldTransform_.translation_.x >= 20.0f || worldTransform_.translation_.y >= 10.0f) {
		isReverse_ = true;
	}
	if (worldTransform_.translation_.x <= -20.0f || worldTransform_.translation_.y <= -10.0f) {
		isReverse_ = false;
	}

	//���˃^�C�}�[�J�E���g�_�E��
	fireTimer--;
	//�w�莞�ԂɒB����
	if (fireTimer <= 0) {
		//�e����
		Fire();
		//���˃^�C�}�[������
		fireTimer = kFireInterval;
	}
	//���񂾂�
	if (life_ <= 0) {
		phase_ = Phase::Leave;
		life_ = 0;
		isDead_ = true;
	}
}

//���E
void Enemy::UpdateLeave() {
	//���x
	Vector3 velocity;

	//�ړ�
	velocity = {0.0f, 0.0f, 0.01f};
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
void Enemy::OnCollisionPlayer() { life_ -= 2; }

void Enemy::OnCollisionOption() { life_--; }