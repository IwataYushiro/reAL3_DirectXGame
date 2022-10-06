#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

//���@�N���X�̑O���錾
class Player;

class Gimmick {
  public:
	Gimmick();
	~Gimmick();

	//
	//�S�̏�����
	void Initialize();
	//�o�l������
	void InitializeSpring();
	
	//�S�̍X�V
	void Update();
	//�o�l�X�V
	void UpdateSpring();
	
	//�S�̕`��
	void Draw(ViewProjection& viewProjection);
	//�o�l�`��
	void DrawSpring(ViewProjection& viewProjection);

	//�e�d�|���̃��[���h���W���擾
	Vector3 GetWorldPositionSpring();
  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransformSpring_;
	//�o�l
	Vector3 SpringPos_;
	//���f���f�[�^
	Model* modelSpring_ = nullptr;	//�o�l
	//�v���[���[�f�[�^
	Player* player_ = nullptr;
	public:
	//�v���[���[�Z�b�g
	void SetPlayer(Player* player) { player_ = player; }
	  void OnCollisionSpring();
};
