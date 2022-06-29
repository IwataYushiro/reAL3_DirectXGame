#include "PlayerBullet.h"

PlayerBullet::PlayerBullet() {}

PlayerBullet::~PlayerBullet() {}

//������
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("texture/playerbullet.png");
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

//�X�V
void PlayerBullet::Update() {
	//���W���ړ�������
	worldTransform_.translation_ += velocity_;
	//�s��X�V
	worldTransform_.PlayerUpdate(worldTransform_);

	//���Ԍo�߂Ŏ��S
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

//�`��
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}