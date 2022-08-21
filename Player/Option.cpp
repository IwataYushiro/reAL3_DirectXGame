#include "Option.h"
#include "Player.h"

//������
void Option::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//�t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("texture/option.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

}

//�X�V
void Option::Update() {	

	worldTransform_.translation_ = {player_->GetWorldPosition().x + 2.0f, player_->GetWorldPosition().y + 2.0f, 0.0f};
}

//�`��
void Option::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
//�I�v�V�����̈ړ�����
void Option::Move() {

}

//�I�v�V�����̐��񏈗�
void Option::Rotate() {

}
