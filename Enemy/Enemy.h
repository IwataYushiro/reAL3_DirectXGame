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
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

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
};

Enemy::Enemy() {}

Enemy::~Enemy() {}