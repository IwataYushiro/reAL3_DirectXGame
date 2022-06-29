#include "Enemy.h"


Enemy::Enemy() {}

Enemy::~Enemy() {}

// ������
  void Enemy::Initialize(Model* model,const Vector3& velocity) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("texture/enemy.png");
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {15.0f, 15.0f, 0.0f};
	velocity_ = velocity;
}

//�X�V
void Enemy::Update() {
	//���W���ړ�������
	worldTransform_.translation_ -= velocity_;
	//�s��X�V
	worldTransform_.PlayerUpdate(worldTransform_);

}

//�`��
void Enemy::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}