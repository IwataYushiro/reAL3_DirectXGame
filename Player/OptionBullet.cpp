#include "OptionBullet.h"
//������
void OptionBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void OptionBullet::Reset() { isDead_ = true; }

//�X�V
void OptionBullet::Update() {
	//���W���ړ�������
	worldTransform_.translation_ += velocity_;
	//�s��X�V
	worldTransform_.Update(worldTransform_);

	//���Ԍo�߂Ŏ��S
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

//�`��
void OptionBullet::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection);
}

//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
void OptionBullet::OnCollision() { isDead_ = true; }

//���[���h���W���擾
Vector3 OptionBullet::GetWorldPosition() {

	//���[���h���W���擾
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}