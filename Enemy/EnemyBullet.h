#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//�G�̒e
class EnemyBullet {
  public:
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

	//���x
	Vector3 velocity_;

	//����
	static const int32_t kLifeTime = 60 * 5;
	//���S����
	int32_t deathTimer_ = kLifeTime;
	//���S�t���O
	bool isDead_ = false;

  public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
};
