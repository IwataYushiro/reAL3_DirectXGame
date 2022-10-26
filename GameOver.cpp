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

	// �t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("gameover.png");

	// �X�v���C�g�̐���
	sprite_ = Sprite::Create(textureHandle_, { 0,0 });
}

void GameOver::Update()
{
	// �����ꂽ��V�[�����ς��
	if (input_->TriggerKey(DIK_SPACE))
	{
		getIsEnd = true;
		nextScene_ = oScene::TITLE;
	}
}

void GameOver::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	sprite_->Draw();

	// �f�o�b�O�e�L�X�g�̕`��
	debugText_->DrawAll(commandList);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}

void GameOver::Reset()
{
	getIsEnd = false;
}
