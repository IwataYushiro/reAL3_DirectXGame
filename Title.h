#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

#include "TextureManager.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"

#include "Clear.h"
#include "GameOver.h"

#include "Scene.h"

class Title
{
public: // �����o�֐�
/// <summary>
/// �R���X�g�N���^
/// </summary>
	Title();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Title();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void Reset();

	oScene GetNextScene() { return nextScene_; }

	int GetChangeFlag() { return changeFlag_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	// �V�[���؂�ւ�
	oScene nextScene_ = oScene::TITLE;
	// �؂�ւ��t���O
	bool changeFlag_ = false;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	//�f�o�b�O�J����
	DebugCamera* debugCamera_ = nullptr;

	// �X�v���C�g
	Sprite* sprite_ = nullptr;
};