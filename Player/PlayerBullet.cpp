#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {}

PlayerBullet::~PlayerBullet() {}

//������
void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("texture/player.png");
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
}

//�X�V
void PlayerBullet::Update() { 
	worldTransform_.PlayerUpdate(worldTransform_); 
}

//�`��
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}