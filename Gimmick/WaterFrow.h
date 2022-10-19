#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

//����

class WaterFlow {
  public:
	WaterFlow();
	~WaterFlow();

	//����������
	void Initialize();

	//�����X�V
	void Update();

	//�����`��
	void Draw(ViewProjection& viewProjection);
	//�����̃��[���h���W���擾
	Vector3 GetWorldPosition();

  private:
	
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f���f�[�^
	Model* model_ = nullptr; //����

	float width_;  //����
	float height_; //�c��
	// float waterFlowRadius;						//���a
	float speed_;                               //���x
	int bright_;    //���邳

	//����
	static const int32_t kLifeTime = 60 * 3;
	//���S����
	int32_t deathTimer_ = kLifeTime;

	bool isActive_; //�����Ă邩

	//����
	void OnCollision();
	float GetSpeed() { return speed_; }
};

