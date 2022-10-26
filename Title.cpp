#include "Title.h"

Title::Title() {}

Title::~Title()
{
	delete sprite_;
}

void Title::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("title.png");

	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, { 0,0 });
}

void Title::Update()
{
	// 押されたらシーンが変わる
	if (input_->TriggerKey(DIK_SPACE))
	{
		changeFlag_ = true;
		nextScene_ = oScene::MANUAL;
	}
}

void Title::Draw()
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

void Title::Reset()
{
	changeFlag_ = false;
}
