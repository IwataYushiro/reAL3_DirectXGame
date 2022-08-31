#pragma once
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "OptionBullet.h"
#include "WorldTransform.h"
#include <cassert>

//���@�N���X�̑O���錾
class Player;
//�I�v�V����(�K���_���ł����t�@���l���݂�����)
class Option {
  public:
	  //�f�X�g���N�^
	~Option();
	//������
	void Initialize(Model* model, const Vector3& position);
	//���Z�b�g����
	void Reset(const Vector3& position);

	//�X�V
	void Update(ViewProjection& viewprojection);
	// 3D���e�B�N��
	void Reticle3D();
	//�`��
	void Draw(ViewProjection& viewProjection);

	//�I�v�V�����̈ړ�����
	void Move(ViewProjection& viewprojection);

	//�I�v�V�����̐��񏈗�
	void Rotate();

	//�I�v�V�����̍U������
	void Attack();

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�e���X�g���擾
	const std::list<std::unique_ptr<OptionBullet>>& GetOptionBullets() { return optionBullets_; }

  private:
	//�e
	std::list<std::unique_ptr<OptionBullet>> optionBullets_;

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// 3D���e�B�N���p
	WorldTransform worldTransform3DReticle_;

	//���f��
	Model* model_ = nullptr;
	Model* modelBullet_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;
	//�v���C���[�̃f�[�^
	Player* player_ = nullptr;

	//�C���v�b�g
	Input* input_ = nullptr;

	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};
