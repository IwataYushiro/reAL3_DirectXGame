#pragma once
#include "DebugText.h"
#include "MyMathUtility.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

//���[���J����
class RailCamera {
  public:
	  //������
	void Initialize(WorldTransform& worldTransform);
	//���Z�b�g
	void Reset();
	//�X�V
	void Update();

	//�`��
	void Draw();

	void SetWorldTransform(WorldTransform& worldTransform) { worldTransform_ = worldTransform; };
	void SetWorldPosition(Vector3& position) { worldTransform_.translation_ = position; };
	void SetWorldRotation(Vector3& rotation) { worldTransform_.rotation_ = rotation; };

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	//��]�p(�x��)
	Vector3 decAngle;
	//��]�p(�J����)
	Vector3 cameraAngle;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
};