#pragma once

#include "Audio.h"
#include "DebugText.h"
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

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�`��
	void Draw(ViewProjection& viewProjection);
	void DrawDead(ViewProjection& viewProjection);

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

  public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
};
