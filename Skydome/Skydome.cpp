#include "Skydome.h"

//������
void Skydome::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	
	model_ = model;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}

//�X�V
void Skydome::Update() {

}

//�`��
void Skydome::Draw(ViewProjection& viewprojection) { 

	//3D���f���`��
	model_->Draw(worldTransform_, viewprojection); 
}
