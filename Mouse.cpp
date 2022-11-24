#include "Mouse.h"
#include "MyMathUtility.h"
#include "WinApp.h"
using namespace DirectX;
using namespace MathUtility;

Matrix4 Mouse::Viewport(float VpWidth, float VpHeight)
{
	Matrix4 matViewport;
	matViewport.m[0][0] = VpWidth / 2;
	matViewport.m[3][0] = -1;
	matViewport.m[3][1] = 1;
	matViewport.m[1][1] = -VpHeight / 2;
	matViewport.m[2][2] = 1;
	matViewport.m[3][3] = 1;
	return matViewport;
}

void Mouse::Initialize(ViewProjection& viewProjection)
{
	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//�e�X�g���f��
	model_ = Model::CreateFromOBJ("cube", true);

	//�N���b�N�t���O
	mouseClick_ = false;

	// ���ʂ̏����l��ݒ�
	plane.normal = DirectX::XMVectorSet(0, 1, 0, 0); // �@���x�N�g��
	plane.distance = 0.0f; // ���_(0,0,0)����̋���

	// ���C�̏����l��ݒ�
	ray.start = DirectX::XMVectorSet(viewProjection.eye.x, viewProjection.eye.y, viewProjection.eye.z, 0);
	ray.dir = DirectX::XMVectorSet(0, 0, 0, 0);

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,0 };
}

void Mouse::Update(ViewProjection& viewProjection)
{
	//�}�E�X�̌��݂̍��W���擾����
	GetCursorPos(&po);
	HWND h = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(h, &po);

	// �}�E�X�̃x�N�g���̏�����
	worldPo = { (float)po.x,(float)po.y,1 };

	// ��̈ړ�����
	if (input_->IsTriggerMouse(0) && mouseClick_ == false)
	{
		mouseClick_ = true;
	}
	else if (input_->IsTriggerMouse(0))
	{
		mouseClick_ = false;
	}

	if (mouseClick_ == true)
	{

	}
	else
	{

	}

	// �}�E�X�̃X�N���[�����W�����[���h���W�ɕϊ�
	Matrix4 matInverseProjection = Matrix4Inverse(viewProjection.matProjection);
	Matrix4 matInverseView = Matrix4Inverse(viewProjection.matView);
	Matrix4 matInverseViewport = Matrix4Inverse(Viewport(1280, 720));

	Matrix4 matInverse = matInverseViewport * matInverseProjection * matInverseView;

	//W���Z
	DivWorldPo = Vector3TransformCoord(worldPo, matInverse);

	//�J��������}�E�X�ւ̃x�N�g��
	vecPo = Vector3(viewProjection.eye.x - DivWorldPo.x,
		viewProjection.eye.y - DivWorldPo.y, viewProjection.eye.z - DivWorldPo.z);

	//���K��
	norVecPo = vecPo.normalize();

	//dir�ɑ��
	ray.dir = DirectX::XMVectorSet(norVecPo.x, norVecPo.y, norVecPo.z, 0);

	// �}�E�X�ƃu���b�N�̓����蔻��
	std::ostringstream raystr;
	raystr << "lay.start("
		<< std::fixed << std::setprecision(2)
		<< ray.start.m128_f32[0] << ","
		<< ray.start.m128_f32[1] << ","
		<< ray.start.m128_f32[2] << ")";


	debugText_->Print(raystr.str(), 50, 180, 1.0f);

	// ���C�ƕ��ʂ̓����蔻��
	XMVECTOR inter;
	float distance;
	bool hit = Collision::CheckRay2Plane(ray, plane, &distance, &inter);
	if (hit) {
		debugText_->Print("HIT", 50, 260, 1.0f);
		// stringstream�����Z�b�g���A��_���W�𖄂ߍ���
		raystr.str("");
		raystr.clear();
		raystr << "("
			<< std::fixed << std::setprecision(2)
			<< inter.m128_f32[0] << ","
			<< inter.m128_f32[1] << ","
			<< inter.m128_f32[2] << ")";

		debugText_->Print(raystr.str(), 50, 280, 1.0f);
	}

	// �s��X�V
	worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(worldTransform_);
	worldTransform_.TransferMatrix();

	debugText_->SetPos(50, 25);
	debugText_->Printf("mousePos_(%d,%d)", po.x, po.y);
	debugText_->SetPos(50, 50);
	debugText_->Printf("mouseClick_(%d)", mouseClick_);
	debugText_->SetPos(50, 75);
	debugText_->Printf("worldTransform_.translation_(%f,%f,%f)", DivWorldPo.x, DivWorldPo.y, DivWorldPo.z);
}

void Mouse::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}