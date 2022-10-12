#pragma once

#include "DebugText.h"
#include "Gimmick.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

class Player {
  public:
	Player();
	~Player();

	//������
	void Initialize(Model* model);
	//���Z�b�g����
	void Reset();
	//���񂾂�
	void Death();
	//�X�V
	void Update(ViewProjection& viewprojection);

	//�v���C���[�̈ړ�����
	void Move();
	//�W�����v����
	void Jump();
	//�ړ���������
	void MoveLimit();

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�`��
	void Draw(ViewProjection& viewProjection);
	void DrawDead(ViewProjection& viewProjection);

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	//�o�l�ƏՓ�
	void OnCollisionSpring();
	//�����ƏՓ�
	void OnCollisionWaterFlow();

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	Model* modelDead_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	//���S�t���O�ƃ��C�t
	bool isDead_ = false;
	int life_ = 5;
	//�j������
	bool isSwim;
	//����(�ς��Ȃ�)
	const float buoyancy = -0.5f;
	//�d��
	float gravity;

	//�d�|��
	Gimmick* gimmick_ = nullptr;
  public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
};
