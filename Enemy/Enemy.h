#pragma once
#include "EnemyBullet.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>
//���@�N���X�̑O���錾
class Player;

//�G
class Enemy {
  public:
	//�e���ˊԊu
	static const int kFireInterval = 60;
	//������
	void Initialize(Model* model);
	//�ڋ߃t�F�[�Y������
	void InitializeApproach();
	//�X�V
	void Update();
	//�e����
	void Fire();
	//���[���h���W���擾
	Vector3 GetWorldPosition();
	//�`��
	void Draw(const ViewProjection& viewProjection);

	//��ԕω��p�̍X�V�֐�
	//�ڋ�
	void UpdateApproach();
	//���E
	void UpdateLeave();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();
	
	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() { return enemyBullets_; }

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�e
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�s���t�F�[�Y
	enum class Phase {
		Approach, //�ڋ�
		Leave,    //���E
	};

	//�t�F�[�Y
	Phase phase_;
	//�e���˃^�C�}�[
	int32_t fireTimer = 0;

	//���@
	Player* player_ = nullptr;

  public:
	void SetPlayer(Player* player) { player_ = player; }
};