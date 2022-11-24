#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "GlobalScene.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include <cassert>
#include <list>
#include <memory>

class Enemy {
public:
	// ��
	enum PIECE {
		NONE,
		PAWN,
		ROOK,
		BISHOP,
		KNIGHT,
		QUEEN,
		KING
	};

	// �\����
	struct PieceData {
		WorldTransform worldTransform_;
		int type_;
	};

public:
	//������
	void Initialize(Model* model);

	//�X�V
	void Update(const Vector3& pos, int phase);

	//�`��
	void Draw(ViewProjection& viewProjection);

	//���Z�b�g����
	void Reset();

	// �Z���N�g
	void Select();

private:
	//�v���C���[�̈ړ�����
	void Move();

	// �`�F�X���
	void PopPlayer(const Vector3& pos);
	void PopPawn(const Vector3& pos);
	void PopRook();
	void PopBishop();
	void PopKnight();
	void PopQueen();
	void PopKing();

private:
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//��
	Audio* audio_ = nullptr;
	//�T�E���h�f�[�^
	uint32_t jumpSound_ = 0;

	// ���[���h�ϊ��f�[�^
	std::list<std::unique_ptr<PieceData>> pieces_;

	// �`�F�X��
	std::list<std::unique_ptr<Pawn>> pawns_;
	std::list<std::unique_ptr<Rook>> rooks_;
	std::list<std::unique_ptr<Bishop>> bishops_;
	std::list<std::unique_ptr<Knight>> knights_;
	std::list<std::unique_ptr<Queen>> queen_;
	std::list<std::unique_ptr<King>> king_;

	// �R�X�g
	int cost_ = 5;

	// Pop�R�}���h�p
	int popCommand_[16];
	int num_ = 0;

	//���S�t���O
	bool isDead_ = false;
	//�}�E�X
	bool mouseClick_;

public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
	int GetCost() { return cost_; }
};
