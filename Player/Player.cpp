#include "Player.h"

void Player::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	audio_ = Audio::GetInstance();

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//音
	jumpSound_ = audio_->LoadWave("sound/se/jump.wav");
  
}

void Player::Update(const Vector3& pos, int phase) {
	
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

void Player::Draw(ViewProjection& viewProjection) {
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

void Player::Reset() {

}

void Player::Select() {
	if (input_->TriggerKey(DIK_0)) {
		popCommand_[num_] = PAWN;
		num_++;
		cost_--;
	}
}

void Player::PopPlayer(const Vector3& pos) {
	// numを0に
	num_ = 0;

	// SPACEを押したらPopCommandに従って生成する
	if (input_->TriggerKey(DIK_SPACE)) {
		switch (popCommand_[num_])
		{
		case NONE:
			// インクリメント
			num_++;

			break;
		case PAWN:
			// ポーンを生成
			PopPawn(pos);

			break;
		}
	}
}

void Player::Move() {

}

void Player::PopPawn(const Vector3& pos) {
	// ポーン生成
	std::unique_ptr<Pawn> pawn = std::make_unique<Pawn>();
	// 初期化
	pawn->Initialize(model_, pos);
	// リストに追加
	pawns_.push_back(std::move(pawn));
}

void Player::PopRook() {
	// ルーク生成
	std::unique_ptr<Rook> rook = std::make_unique<Rook>();
	// 初期化
	rook->Initialize(model_);
	// リストに追加
	rooks_.push_back(std::move(rook));
}

void Player::PopBishop() {
	// ビショップ生成
	std::unique_ptr<Bishop> bishop = std::make_unique<Bishop>();
	// 初期化
	bishop->Initialize(model_);
	// リストに追加
	bishops_.push_back(std::move(bishop));
}

void Player::PopKnight() {
	// ナイト生成
	std::unique_ptr<Knight> knight = std::make_unique<Knight>();
	// 初期化
	knight->Initialize(model_);
	// リストに追加
	knights_.push_back(std::move(knight));
}

void Player::PopQueen() {
	// クイーン生成
	std::unique_ptr<Queen> queen = std::make_unique<Queen>();
	// 初期化
	queen->Initialize(model_);
	// リストに追加
	queen_.push_back(std::move(queen));
}

void Player::PopKing() {
	// キング生成
	std::unique_ptr<King> king = std::make_unique<King>();
	// 初期化
	king->Initialize(model_);
	// リストに追加
	king_.push_back(std::move(king));
}