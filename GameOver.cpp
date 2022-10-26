#include "GameOver.h"

GameOver::GameOver() {}

GameOver::~GameOver()
{
	delete sprite_;
}

void GameOver::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("gameover.png");

	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, { 0,0 });
}

void GameOver::Update()
{
	// 押されたらシーンが変わる
	if (input_->TriggerKey(DIK_SPACE))
	{
		getIsEnd = true;
		nextScene_ = oScene::TITLE;
	}
}

void GameOver::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameOver::Reset()
{
	getIsEnd = false;
}
