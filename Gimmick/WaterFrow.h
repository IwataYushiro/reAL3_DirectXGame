#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

//����

class WaterFlow {
  public:
	~WaterFlow();

	//����������
	void Initialize(const Vector3& position, const Vector3& velocity);
	//���Z�b�g
	void Reset();

	//�����X�V
	void Update();

	//�����`��
	void Draw(ViewProjection& viewProjection);
	//�����̃��[���h���W���擾
	Vector3 GetWorldPosition();

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�e�N�X�`��
	uint32_t texWaterFlow_ = 0;
	//���f���f�[�^
	Model* model_ = nullptr; //����

	float width_;  //����
	float height_; //�c��
	// float waterFlowRadius;						//���a
	Vector3 speed_; //���x
	int bright_;    //���邳

	//����
	static const int32_t kLifeTime = 60 * 3;
	//���S����
	int32_t deathTimer_ = kLifeTime;

	bool isActive_ = false; //�����Ă邩

  public:
	//�A�N�Z�b�T
	//����
	void OnCollision();
	bool IsActive() const { return isActive_; }
};
