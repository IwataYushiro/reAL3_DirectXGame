#include "Mouse.h"
using namespace DirectX;

void Mouse::Initialize(ViewProjection& viewProjection)
{
	//�V���O���g���C���X�^���X���擾
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	mouseClick_ = false;

	// ���ʂ̏����l��ݒ�
	plane.normal = DirectX::XMVectorSet(0, 1, 0, 0); // �@���x�N�g��
	plane.distance = 0.0f; // ���_(0,0,0)����̋���

	// ���C�̏����l��ݒ�
	ray.start = DirectX::XMVectorSet(viewProjection.eye.x, viewProjection.eye.y, viewProjection.eye.z, 0);
	ray.dir = DirectX::XMVectorSet(0, 0, 0, 0);
}

void Mouse::Update()
{
	//�}�E�X�̌��݂̍��W���擾����
	GetCursorPos(&po);

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

	{
		ray.dir += XMVectorSet(po.x, po.y, 100, 0);
	}

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

	debugText_->SetPos(50, 25);
	debugText_->Printf("mousePos_(%d,%d)", po.x, po.y);
	debugText_->SetPos(50, 50);
	debugText_->Printf("mouseClick_(%d)", mouseClick_);
}