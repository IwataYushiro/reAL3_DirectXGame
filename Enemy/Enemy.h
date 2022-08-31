#pragma once
#include "DebugText.h"
#include "EnemyBullet.h"
#include "GlobalScene.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>
//���@�N���X�̑O���錾
class Player;
//�Q�[���V�[����
class GameScene;
//�G
class Enemy {
  public:
	~Enemy();
	//�e���ˊԊu
	static const int kFireInterval = 60;
	//������
	void Initialize(Model* model);
	//�ڋ߃t�F�[�Y������
	void InitializeApproach();
	//���Z�b�g����
	void Reset();
	//�p�����[�^
	void Stage1Parameter();
	void Stage2Parameter();
	//�X�V
	void Update();
	//�e����
	void Fire();
	//���[���h���W���擾
	Vector3 GetWorldPosition();
	//�`��
	void DrawStage1(const ViewProjection& viewProjection);
	void DrawStage2(const ViewProjection& viewProjection);

	//��ԕω��p�̍X�V�֐�
	//�ڋ�
	void UpdateApproachStage1();
	void UpdateApproachStage2();
	//�U��
	void UpdateAttackStage1();
	void UpdateAttackStage2();
	//���E
	void UpdateLeave();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollisionPlayer();
	void OnCollisionOption();

	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() { return enemyBullets_; }

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�e
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
	//���f��
	Model* modelStage1_ = nullptr;
	Model* modelDeadStage1_ = nullptr;

	Model* modelStage2_ = nullptr;
	Model* modelDeadStage2_ = nullptr;
	Model* modelBullet_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�s���t�F�[�Y
	enum class Phase {
		//��������X�e�[�W1
		ApproachStage1, //�ڋ�
		AttackStage1,   //�U��
		
		//��������X�e�[�W2
		ApproachStage2,  //�ڋ�
		AttackStage2,    //�U��

		//�S��
		Leave,    //���E
	};

	//�t�F�[�Y
	Phase phase_;
	//�e���˃^�C�}�[
	int32_t fireTimer = 0;

	//���@
	Player* player_ = nullptr;
	//�Q�[���V�[��
	GameScene* gameScene_ = nullptr;

	//���S�t���O�ƃ��C�t
	bool isDead_ = false;
	int life_ = 15;
	//���]�t���O
	bool isReverse_ = false;

  public:
	bool IsDead() const { return isDead_; }
	void SetPlayer(Player* player) { player_ = player; }
};
