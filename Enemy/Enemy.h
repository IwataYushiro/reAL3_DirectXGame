#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//�G

class Enemy {
  public:
	Enemy();
	~Enemy();

	//������
	void Initialize(Model* model, const Vector3& velocity);

	//�X�V
	void Update();

	//�`��
	void Draw(const ViewProjection& viewProjection);

  private:

	  //���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//���x
	Vector3 velocity_ = {0.1f,0.1f,0.0f};

	public: //�A�N�Z�b�T�A�C�����C���֐�
	
	Vector3	GetVelocity() { return velocity_; }
};
