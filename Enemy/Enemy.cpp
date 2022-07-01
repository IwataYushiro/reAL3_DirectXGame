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
	worldTransform_.translation_ = {15.0f, 15.0f, 0.0f};

}

//�X�V
void Enemy::Update() {
	//���W���ړ�������
	//���x
	Vector3 velocity_(0.1f, 0.1f, 0.0f);
	worldTransform_.translation_ -= velocity_;
	//�s��X�V
	worldTransform_.Update(worldTransform_);

}

//�`��
void Enemy::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}