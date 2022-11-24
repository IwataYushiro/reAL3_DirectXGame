#include "Enemy.h"

void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	audio_ = Audio::GetInstance();

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//��
	jumpSound_ = audio_->LoadWave("sound/se/jump.wav");

}

void Enemy::Update(const Vector3& pos, int phase) {

	switch (phase)
	{
	case POP:
		break;
	case MOVE:
		break;
	case ATTACK:
		break;
	}
	for (std::unique_ptr<Pawn>& pawn : pawns_) {
		pawn->Update();
	}

}

void Enemy::Draw(ViewProjection& viewProjection) {
	for (std::unique_ptr<Pawn>& pawn : pawns_) {
		pawn->Draw(viewProjection);
	}
	for (std::unique_ptr<Rook>& rook : rooks_) {
		rook->Draw(viewProjection);
	}
	for (std::unique_ptr<Bishop>& bishop : bishops_) {
		bishop->Draw(viewProjection);
	}
	for (std::unique_ptr<Knight>& knight : knights_) {
		knight->Draw(viewProjection);
	}
	for (std::unique_ptr<Queen>& queen : queen_) {
		queen->Draw(viewProjection);
	}
	for (std::unique_ptr<King>& king : king_) {
		king->Draw(viewProjection);
	}
}

void Enemy::Reset() {

}

void Enemy::Select() {
	if (input_->TriggerKey(DIK_0)) {
		popCommand_[num_] = PAWN;
		num_++;
		cost_--;
	}
}

void Enemy::PopPlayer(const Vector3& pos) {
	// num��0��
	num_ = 0;

	// SPACE����������PopCommand�ɏ]���Đ�������
	if (input_->TriggerKey(DIK_SPACE)) {
		switch (popCommand_[num_])
		{
		case NONE:
			// �C���N�������g
			num_++;

			break;
		case PAWN:
			// �|�[���𐶐�
			PopPawn(pos);

			break;
		}
	}
}

void Enemy::Move() {

}

void Enemy::PopPawn(const Vector3& pos) {
	// �|�[������
	std::unique_ptr<Pawn> pawn = std::make_unique<Pawn>();
	// ������
	pawn->Initialize(model_, pos);
	// ���X�g�ɒǉ�
	pawns_.push_back(std::move(pawn));
}

void Enemy::PopRook() {
	// ���[�N����
	std::unique_ptr<Rook> rook = std::make_unique<Rook>();
	// ������
	rook->Initialize(model_);
	// ���X�g�ɒǉ�
	rooks_.push_back(std::move(rook));
}

void Enemy::PopBishop() {
	// �r�V���b�v����
	std::unique_ptr<Bishop> bishop = std::make_unique<Bishop>();
	// ������
	bishop->Initialize(model_);
	// ���X�g�ɒǉ�
	bishops_.push_back(std::move(bishop));
}

void Enemy::PopKnight() {
	// �i�C�g����
	std::unique_ptr<Knight> knight = std::make_unique<Knight>();
	// ������
	knight->Initialize(model_);
	// ���X�g�ɒǉ�
	knights_.push_back(std::move(knight));
}

void Enemy::PopQueen() {
	// �N�C�[������
	std::unique_ptr<Queen> queen = std::make_unique<Queen>();
	// ������
	queen->Initialize(model_);
	// ���X�g�ɒǉ�
	queen_.push_back(std::move(queen));
}

void Enemy::PopKing() {
	// �L���O����
	std::unique_ptr<King> king = std::make_unique<King>();
	// ������
	king->Initialize(model_);
	// ���X�g�ɒǉ�
	king_.push_back(std::move(king));
}