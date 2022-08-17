#include "Enemy.h"


Enemy::Enemy() {}

Enemy::~Enemy() {}

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

}

//�X�V
void Enemy::Update() {
	//���W���ړ�������
	
	//���x
	Vector3 velocity_;
	
	switch (phase_) {
	case Enemy::Phase::Approach:
	
	
		//�ړ�
		velocity_ = {0.0f, 0.0f, -0.1f};
		worldTransform_.translation_ += velocity_;
		
		//�w��̈ʒu�ɓ��B�����痣�E
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;

	case Enemy::Phase::Leave:
		//�ړ�
		velocity_ = {0.1f, 0.1f, 0.0f};
		worldTransform_.translation_ += velocity_;
		break;
	}
	
	//�s��X�V
	worldTransform_.Update(worldTransform_);

}

//�`��
void Enemy::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}