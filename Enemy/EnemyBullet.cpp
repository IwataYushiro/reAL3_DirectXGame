#include "EnemyBullet.h"

//������
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULL�|�C���^�`�F�b�N
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
void EnemyBullet::Reset() { isDead_ = true; }
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

//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
void EnemyBullet::OnCollision() { isDead_ = true; }

//���[���h���W���擾
Vector3 EnemyBullet::GetWorldPosition() {

	//���[���h���W���擾
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}