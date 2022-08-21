#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
//���@�N���X�̑O���錾
class Player;
//�I�v�V����(�K���_���ł����t�@���l���݂�����)
class Option {
  public:
	//������
	void Initialize(Model* model);

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection& viewProjection);

	//�I�v�V�����̈ړ�����
	void Move();

	//�I�v�V�����̐��񏈗�
	void Rotate();

	//�I�v�V�����̍U������
	void Attack();

	//���[���h���W���擾
	Vector3 GetWorldPosition();

  private:
	  
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�v���C���[�̃f�[�^
	Player* player_ = nullptr;
};
