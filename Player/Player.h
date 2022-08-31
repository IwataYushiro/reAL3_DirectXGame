#pragma once

#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "Option.h"
#include "PlayerBullet.h"
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

	//�X�V
	void Update(ViewProjection& viewprojection);

	//�v���C���[�̈ړ�����
	void Move();

	//�v���C���[�̐��񏈗�
	void Rotate();

	//�v���C���[�̍U������
	void Attack();

	//�ړ���������
	void MoveLimit();

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�`��
	void Draw(ViewProjection& viewProjection);

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

  private:
	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	//�I�v�V����
	Option* option_ = nullptr;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	Model* modelOption_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	//���S�t���O�ƃ��C�t
	bool isDead_ = false;
	int life_ = 5;

  public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
	Option* GetOption() const { return option_; }
};
