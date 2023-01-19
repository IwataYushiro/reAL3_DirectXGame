#include "Enemy.h"

void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	audio_ = Audio::GetInstance();

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//��
	jumpSound_ = audio_->LoadWave("sound/se/jump.wav");

}

void Enemy::Update(const Vector3& pos, int phase) {

}

void Enemy::Draw(ViewProjection& viewProjection) {
}

void Enemy::Reset() {

}

void Enemy::Move() {

}