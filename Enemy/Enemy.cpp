#include "Enemy.h"
#include "GameScene.h"
#include "Player.h"
// ������
Enemy::~Enemy() {
	delete modelBullet_;
	delete modelDeadStage1_;

	delete modelStage2_;
	delete modelDeadStage2_;

	delete modelStage3_;
	delete modelSaveStage3_;
}

void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	modelStage1_ = model;
	modelDeadStage1_ = Model::CreateFromOBJ("enemy1dead", true);

	modelStage2_ = Model::CreateFromOBJ("enemy2", true);
	modelDeadStage2_ = Model::CreateFromOBJ("enemy2dead", true);

	modelStage3_ = Model::CreateFromOBJ("enemy3", true);
	modelSaveStage3_ = Model::CreateFromOBJ("enemy3save", true);

	modelBullet_ = Model::CreateFromOBJ("enemybullet", true);
	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	isReverse_ = false;
	//�����X�e�[�W
	Stage1Parameter();
}

//�p�����[�^
void Enemy::Stage1Parameter() {
	worldTransform_.translation_ = {-10.0f, -5.0f, 80.0f};
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();
	//�����t�F�[�Y
	phase_ = Phase::ApproachStage1;

	//���˃^�C�}�[������
	fireTimer = kFireIntervalStage1;

	life_ = 40;
	isDead_ = false;

	isReverse_ = false;
	//�e���Z�b�g
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Reset();
	}
}

void Enemy::Stage2Parameter() {
	worldTransform_.translation_ = {5.0f, 5.0f, 100.0f};
	//�����t�F�[�Y
	phase_ = Phase::ApproachStage2;
	//���˃^�C�}�[������
	fireTimer = kFireIntervalStage2;

	life_ = 60;
	isDead_ = false;

	isReverse_ = false;
	//�e���Z�b�g
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Reset();
	}
}

void Enemy::Stage3Parameter() {
	worldTransform_.translation_ = {0.0f, 10.0f, 100.0f};
	//�����t�F�[�Y
	phase_ = Phase::ApproachStage3;
	//���˃^�C�}�[������
	fireTimer = kFireIntervalStage3;

	life_ = 100;
	isDead_ = false;

	isReverse_ = false;
	//�e���Z�b�g
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Reset();
	}
}
//���Z�b�g
void Enemy::Reset() { Stage1Parameter(); }

//�G���f�B���O�p�̃|�W�V����
void Enemy::EndingPosition() {
	worldTransform_.translation_ = {10.0f, -10.0f, -10.0f};
	//��]���x
	const float kRotSpeed = -0.05f;
	worldTransform_.rotation_ = {0.0f, kRotSpeed, 0.0f};
}
//�X�V
void Enemy::Update() {
	//�e�L�X�g�T�C�Y
	debugText_->SetScale(1.0f);
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
			debugText_->SetPos(50, 150);
			debugText_->Printf("!DANGER! pos.z < 0 = DEATH!:(%f)", worldTransform_.translation_.z);
			break;

		case Enemy::Phase::AttackStage2:

			UpdateAttackStage2();
			debugText_->SetPos(50, 150);
			debugText_->Printf("!DANGER! pos.z < 0 = DEATH!:(%f)", worldTransform_.translation_.z);
			break;

			//�X�e�[�W3
		case Enemy::Phase::ApproachStage3:

			UpdateApproachStage3();
			debugText_->SetPos(50, 150);
			debugText_->Printf(
			  "!CHALLENGE! pos.z < 0 or life < 0 = clear!:(posz %f)",
			  worldTransform_.translation_.z);
			break;

		case Enemy::Phase::AttackStage3:

			UpdateAttackStage3();
			debugText_->SetPos(50, 150);
			debugText_->Printf(
			  "!CHALLENGE! pos.z < 0 or life < 0 = clear!:(posz %f)",
			  worldTransform_.translation_.z);
			break;
		}
		//�e�X�V
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Update();
		}
		//���C�t�\��

		debugText_->SetPos(50, 100);
		debugText_->Printf("enemy life:(%d)", life_);
	} else {
		//���W���ړ�������
		switch (phase_) {
		case Enemy::Phase::Leave:
			UpdateLeave();
			break;
		case Enemy::Phase::SaveStage3:
			UpdateSaveStage3();
			break;
		case Enemy::Phase::end:
			EndingPosition();
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
		modelStage1_->Draw(worldTransform_, viewProjection);

		//�e�`��
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(viewProjection);
		}
	} else {
		//���f���̕`��
		modelDeadStage1_->Draw(worldTransform_, viewProjection);
	}
}

void Enemy::DrawStage2(const ViewProjection& viewProjection) {
	if (!isDead_) {
		//���f���̕`��
		modelStage2_->Draw(worldTransform_, viewProjection);

		//�e�`��
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(viewProjection);
		}
	} else {
		//���f���̕`��
		modelDeadStage2_->Draw(worldTransform_, viewProjection);
	}
}

void Enemy::DrawStage3(const ViewProjection& viewProjection) {
	if (!isDead_) {
		//���f���̕`��
		modelStage3_->Draw(worldTransform_, viewProjection);

		//�e�`��
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
			bullet->Draw(viewProjection);
		}
	} else {
		//���f���̕`��
		modelSaveStage3_->Draw(worldTransform_, viewProjection);
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
		fireTimer = kFireIntervalStage1;
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
		fireTimer = kFireIntervalStage2;
	}
	if (worldTransform_.translation_.z < 80.0f) {
		phase_ = Phase::AttackStage2;
	}
}
void Enemy::UpdateApproachStage3() {
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
		fireTimer = kFireIntervalStage3;
	}
	if (worldTransform_.translation_.z < 70.0f) {
		phase_ = Phase::AttackStage3;
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
		fireTimer = kFireIntervalStage1;
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
	//���]���x
	Vector3 velocityReverse;

	//�ړ�
	velocity = {0.2f, 0.2f, -0.03f};
	velocityReverse = {-0.2f, -0.2f, -0.03f};
	if (isReverse_) {
		worldTransform_.translation_ += velocityReverse;
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
		fireTimer = kFireIntervalStage2;
	}
	//���񂾂�
	if (life_ <= 0) {
		phase_ = Phase::Leave;
		life_ = 0;
		isDead_ = true;
	}
}

void Enemy::UpdateAttackStage3() {

	//���x
	Vector3 velocity;
	//���]���x
	Vector3 velocityReverse;

	//�ړ�
	velocity = {0.2f, 0.2f, -0.02f};
	velocityReverse = {0.2f, -0.2f, -0.02f};

	if (isReverse_) {
		worldTransform_.translation_ += velocityReverse;
	} else {
		worldTransform_.translation_ += velocity;
	}

	//�w��̈ʒu�ɓ��B�����甽�]
	if (worldTransform_.translation_.y >= 18.0f) {
		isReverse_ = true;
	}
	if (worldTransform_.translation_.y <= -18.0f) {
		isReverse_ = false;
	}

	if (worldTransform_.translation_.x >= 30.0f) {
		worldTransform_.translation_.x = -30.0f;
	}

	//���˃^�C�}�[�J�E���g�_�E��
	fireTimer--;
	//�w�莞�ԂɒB����
	if (fireTimer <= 0) {
		//�e����
		Fire();
		//���˃^�C�}�[������
		fireTimer = kFireIntervalStage3;
	}
	//���񂾂�
	if (life_ <= 0) {
		phase_ = Phase::SaveStage3;
		life_ = 0;
		isDead_ = true;
	}
	if (worldTransform_.translation_.z <= -10.0f) {
		phase_ = Phase::end;
	}
}
//���E
void Enemy::UpdateLeave() {
	//���x
	Vector3 velocity;

	//�ړ�
	velocity = {0.0f, 0.0f, 0.03f};
	worldTransform_.translation_ += velocity;
}

//�X�e�[�W3���藣�E
void Enemy::UpdateSaveStage3() {
	//���x
	Vector3 velocity;

	//�ړ�
	velocity = {0.0f, 0.0f, -0.05f};
	worldTransform_.translation_ += velocity;
	if (input_->TriggerKey(DIK_SPACE)) {
		phase_ = Phase::end;
	}
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