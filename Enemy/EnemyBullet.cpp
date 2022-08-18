#include "EnemyBullet.h"

//������
void EnemyBullet::Initialize(Model* model, const Vector3& position) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("texture/enemybullet.png");

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
}

//�X�V
void EnemyBullet::Update() {

	//���[���h�s��X�V
	worldTransform_.Update(worldTransform_);
}

//�`��
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//���f���`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}