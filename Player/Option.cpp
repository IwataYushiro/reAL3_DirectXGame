#include "Option.h"
#include "Player.h"
#include <WinApp.h>
//������
void Option::Initialize(Model* model, const Vector3& position) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//�t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("texture/option.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	// 3D���e�B�N��������
	worldTransform3DReticle_.Initialize();
	////�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {position.x + 4.0f, position.y + 4.0f, 0.0f};
}
void Option::Reset(const Vector3& position) {
	worldTransform_.translation_ = MyMathUtility::MySetVector3Zero();

	//�e���Z�b�g
	for (std::unique_ptr<OptionBullet>& bullet : optionBullets_) {
		bullet->Reset();
	}
}

//�X�V
void Option::Update(ViewProjection& viewprojection) {

	//���S�t���O�̗������e���폜
	optionBullets_.remove_if(
	  [](std::unique_ptr<OptionBullet>& bullet) { return bullet->IsDead(); });

	// 3D���e�B�N��
	Reticle3D();
	//�ړ�
	Move(viewprojection);
	//�U��
	Attack();
	//�e�X�V
	for (std::unique_ptr<OptionBullet>& bullet : optionBullets_) {
		bullet->Update();
	}

	//�s��X�V
	worldTransform_.Update(worldTransform_);
}

//�`��
void Option::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
	//�e�`��
	for (std::unique_ptr<OptionBullet>& bullet : optionBullets_) {
		bullet->Draw(viewProjection);
	}
}

// 3D���e�B�N������
void Option::Reticle3D() {
	//�I�v�V��������3D���e�B�N���̋���
	const float kDistanseOptionTo3DReticle = 50.0f;
	//�I�v�V��������3D���e�B�N���ւ̃I�t�Z�b�g
	Vector3 offset = {0.0f, 0.0f, 1.0f};
	//���[���h�s��̉�]�𔽉f
	offset = MyMathUtility::MyVector3TransformNormal(offset, worldTransform_.matWorld_);
	//�����𐮂���
	offset = MyMathUtility::MyVector3Normalize(offset) *= kDistanseOptionTo3DReticle;
	// 3D���e�B�N���̍��W������
	worldTransform3DReticle_.translation_ = {
	  worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z + kDistanseOptionTo3DReticle};
}
//�I�v�V�����̈ړ�����
void Option::Move(ViewProjection& viewprojection) {
	Vector3 move = MyMathUtility::MySetVector3Zero();
	float moveSpeed = 0.3f;

	//�L�[�{�[�h���͂ɂ��ړ�����
	Matrix4 matTrans = MyMathUtility::MySetMatrix4Identity();
	if (input_->PushKey(DIK_LEFT)) {
		move.x = -moveSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x = moveSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y = moveSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y = -moveSpeed;
	}

	worldTransform_.translation_ += move;
}

//�I�v�V�����̐��񏈗�
void Option::Rotate() {

	Vector3 angle = MyMathUtility::MySetVector3Zero();
	float angleSpeed = 0.1f;

	if (input_->PushKey(DIK_A)) {
		angle.y -= angleSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		angle.y += angleSpeed;
	}

	worldTransform_.rotation_ += angle;
}

//�I�v�V�����̍U������
void Option::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		//�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0.0f, 0.0f, kBulletSpeed);

		velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
		//�I�v�V�����̍��W���R�s�[
		Vector3 position = worldTransform_.translation_;

		//�e�𐶐���������
		std::unique_ptr<OptionBullet> newBullet = std::make_unique<OptionBullet>();
		newBullet->Initialize(model_, position, velocity);

		//�e��o�^
		optionBullets_.push_back(std::move(newBullet));
		//���郁�����̏��L��������unique_ptr�͂�����������݂ł��Ȃ�
		//���̏��L�������n���邽�߂̋@�\�� std::move()
	}
}