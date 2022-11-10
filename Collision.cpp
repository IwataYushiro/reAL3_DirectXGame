#include "Collision.h"

using namespace DirectX;

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, 
	DirectX::XMVECTOR* inter)
{
	const float epsilon = 1.0e-5f; // �덷�z���p�̔����Ȓl
	// �ʖ@���ƃ��C�̕����x�N�g���̓���
	float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon) { return false; }
	// �n�_�ƌ��_�̋���(���ʂ̖@������)
	// �ʖ@���ƃ��C�̎n�_���W(�ʒu�x�N�g��)�̓���
	float d2 = XMVector3Dot(plane.normal, ray.start).m128_f32[0];
	// �n�_�ƕ��ʂ̋���(���ʂ̖@������)
	float dist = d2 - plane.distance;
	// �n�_�ƕ��ʂ̋���(���C����)
	float t = dist / -d1;
	// ��_���n�_�����ɂ���̂ŁA������Ȃ�
	if (t < 0)return false;
	// ��������������
	if (distance) { *distance = t; }
	// ��_���v�Z
	if (inter) { *inter = ray.start + t * ray.dir; }
	return true;
}
