#include "EnemyBullet.h"

//������
void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("texture/enemybullet.png");

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

//�X�V
void EnemyBullet::Update() {
	//���W�ړ�
	worldTransform_.translation_ += velocity_;
	//���[���h�s��X�V
	worldTransform_.Update(worldTransform_);

	//���Ԍo�߂Ŏ��S
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

//�`��
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//���f���`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}