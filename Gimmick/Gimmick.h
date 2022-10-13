#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

//���@�N���X�̑O���錾
class Player;

class Gimmick {
  public:
	Gimmick();
	~Gimmick();

	//
	//�������p�[�e�B�N���������邽�߂̕ϐ�
	static const int WATERFLOW_MAX_ = 500; //�ő��

	//�S�̏�����
	void Initialize();
	//�o�l������
	void InitializeSpring();
	//����������
	void InitializeWaterFlow();

	//�S�̍X�V
	void Update();
	//�����X�V
	void UpdateWaterFlow();

	//�S�̕`��
	void Draw(ViewProjection& viewProjection);
	//�o�l�`��
	void DrawSpring(ViewProjection& viewProjection);
	//�����`��
	void DrawWaterFlow(ViewProjection& viewProjection);
	
	//�e�d�|���̃��[���h���W���擾
	Vector3 GetWorldPositionSpring();

	Vector3& GetWorldPositionWaterFlow();

  private:
	//�o�l
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransformSpring_;
	//���f���f�[�^
	Model* modelSpring_ = nullptr; //�o�l

	//����
	
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransformWaterFlow_[WATERFLOW_MAX_];
	//���f���f�[�^
	Model* modelWaterFlow_ = nullptr; //����

	float waterFlowWidth_;							//����
	float waterFlowHeight_;							//�c��
	//float waterFlowRadius;						//���a
	float waterFlowSpeed_;							//���x
	int waterFlowBright_[WATERFLOW_MAX_];			//���邳
	bool isActiveWaterFlow_[WATERFLOW_MAX_];		//�����Ă邩

	//�v���[���[�f�[�^
	Player* player_ = nullptr;

  public:
	//�v���[���[�Z�b�g
	void SetPlayer(Player* player) { player_ = player; }
	//�o�l
	void OnCollisionSpring();
	//����
	void OnCollisionWaterFlow();
	float GetWaterFlowSpeed() { return waterFlowSpeed_; }
	static const int GetWaterFlowMaxInit() { return WATERFLOW_MAX_; }
};
