#pragma once
#include "Audio.h"
#include "Model.h"
#include "TextureManager.h"
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
	//��
	Audio* audio_ = nullptr;
	
	//�o�l
	uint32_t springSe_ = 0;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransformSpring_;
	
	//�e�N�X�`��
	uint32_t texSpring_ = 0;
	//���f���f�[�^
	Model* modelSpring_ = nullptr; //�o�l

	//����
	std::list<std::unique_ptr<WaterFlow>> waterFlow_;
	Vector3 waterFlowPosition_;
	//�v���[���[�f�[�^
	Player* player_ = nullptr;

  public:
	//�v���[���[�Z�b�g
	void SetPlayer(Player* player) { player_ = player; }
	//�o�l
	void OnCollisionSpring();
	
	void SetWorldPositionSpring(Vector3 position) { worldTransformSpring_.translation_ = position; }

	void SetPositionWaterFlow(Vector3 position) { waterFlowPosition_ = position; }
};
