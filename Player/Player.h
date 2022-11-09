#pragma once

#include "Audio.h"
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
	// �j��(����)
	void Swim();
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
	// �X�e�[�W�Ƃ̓����蔻��
	void OnCollisionBlock();
	void OnCollisionStep();
	void OnCollisionWall();
	void OffCollisionBlock();

  private:
	//��
	Audio* audio_ = nullptr;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	Model* modelDead_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�C���v�b�g
	Input* input_ = nullptr;
	//�T�E���h�f�[�^
	uint32_t jumpSound_ = 0;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	//���S�t���O�ƃ��C�t
	bool isDead_ = false;
	int life_ = 5;
	//�j������
	bool isSwim;
	// �W�����v���Ă��邩
	bool isJump;
	//����(�ς��Ȃ�)
	const float buoyancy = -0.5f;
	//�d��
	float gravity;
	// 1�t���[���O�̎��@�̈ʒu
	Vector3 prePosition_;
	// �}�E�X�̍��W
	POINT po;
	// �N���b�N�t���O
	bool mouseClick_;

	//�d�|��
	Gimmick* gimmick_ = nullptr;
  public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
};
