#pragma once
#include "EnemyBullet.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

//�G
class Enemy {
  public:
	Enemy();
	~Enemy();

	//������
	void Initialize(Model* model);

	//�X�V
	void Update();
	//�e����
	void Fire();

	//�`��
	void Draw(const ViewProjection& viewProjection);

	//��ԕω��p�̍X�V�֐�
	//�ڋ�
	void UpdateApproach();
	//���E
	void UpdateLeave();

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�e
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ�
		Leave,    //���E
	};

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
};
