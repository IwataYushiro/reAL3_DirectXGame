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

	// �t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("title.png");

	// �X�v���C�g�̐���
	sprite_ = Sprite::Create(textureHandle_, { 0,0 });
}

void Title::Update()
{
	// �����ꂽ��V�[�����ς��
	if (input_->TriggerKey(DIK_SPACE))
	{
		changeFlag_ = true;
		nextScene_ = oScene::MANUAL;
	}
}

void Title::Draw()
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

void Title::Reset()
{
	changeFlag_ = false;
}
