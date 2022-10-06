#include "Skydome.h"

Skydome::~Skydome() { delete railcamera_; }
//������
void Skydome::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����

	model_ = model;
	railcamera_ = new RailCamera();
	
	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	railcamera_->Initialize(worldTransform_);
}
//���Z�b�g
void Skydome::Reset() { railcamera_->Reset(); }
//�X�V
void Skydome::Update() { railcamera_->Update(); }

//�`��
void Skydome::Draw(ViewProjection& viewprojection) {

	// 3D���f���`��
	model_->Draw(worldTransform_, viewprojection);
}
