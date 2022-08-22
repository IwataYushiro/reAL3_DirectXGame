#include "Option.h"
#include "Player.h"

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
	////�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {position.x + 4.0f, position.y + 4.0f, 0.0f};
	
}

//�X�V
void Option::Update() {	
	//�ړ�
	Move();
	//��]
	Rotate();  
	//�U��
	
	//�s��X�V
	worldTransform_.Update(worldTransform_);
}

//�`��
void Option::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//�I�v�V�����̈ړ�����
void Option::Move() {
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
