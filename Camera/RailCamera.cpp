#include "RailCamera.h"

void RailCamera::Initialize(WorldTransform& worldTransform) {
	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_ = worldTransform;
	
	//�r���[�v���W�F�N�V����������

	this->viewProjection_.Initialize();
	//�f�o�b�N�e�L�X�g
	debugText_ = DebugText::GetInstance();
}
//���Z�b�g
void RailCamera::Reset() { 
	worldTransform_.translation_ = MyMathUtility::MySetVector3Zero(); 
	worldTransform_.rotation_ = MyMathUtility::MySetVector3Zero();
}
  //�X�V
void RailCamera::Update() {
	Vector3 velocity = {0.0f, 0.0f, 0.02f};
	Vector3 angle = {0.0f, MyMathUtility::GetRadian(cameraAngle.y), 0.0f};

	cameraAngle.y += 0.1f;
	worldTransform_.rotation_ = angle;
	//�s��̍Čv�Z
	worldTransform_.Update(worldTransform_);

	viewProjection_.eye = worldTransform_.translation_;
	//���[���h�O���x�N�g��
	Vector3 forward(0.0f, 0.0f, 1.0f);
	//���[���J�����̉�]�𔽉f
	forward = worldTransform_.rotation_;
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_.target = viewProjection_.eye += forward;
	//���[���h������x�N�g��
	Vector3 up(0.0f, 1.0f, 0.0f);
	//���[���J�����̉�]�𔽉f
	viewProjection_.up = worldTransform_.rotation_ += up;
	//�r���[�v���W�F�N�V�������X�V
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

//�`��
void RailCamera::Draw() {}
