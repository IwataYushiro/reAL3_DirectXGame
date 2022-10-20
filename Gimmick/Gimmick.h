#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "WaterFrow.h"
#include <list>
#include <memory>

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
	
	//�S�̍X�V
	void Update();
	
	//�S�̕`��
	void Draw(ViewProjection& viewProjection);
	//�o�l�`��
	void DrawSpring(ViewProjection& viewProjection);
	
	//�e�d�|���̃��[���h���W���擾
	Vector3 GetWorldPositionSpring();
	//�������X�g���擾
	const std::list<std::unique_ptr<WaterFlow>>& GetWaterFlow() { return waterFlow_; }
  private:
	//�o�l
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransformSpring_;
	//���f���f�[�^
	Model* modelSpring_ = nullptr; //�o�l

	//����
	std::list<std::unique_ptr<WaterFlow>> waterFlow_;
	//�v���[���[�f�[�^
	Player* player_ = nullptr;

  public:
	//�v���[���[�Z�b�g
	void SetPlayer(Player* player) { player_ = player; }
	//�o�l
	void OnCollisionSpring();
	
};
