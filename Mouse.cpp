#include "Mouse.h"
using namespace DirectX;

void Mouse::Initialize(ViewProjection& viewProjection)
{
	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	mouseClick_ = false;

	// 平面の初期値を設定
	plane.normal = DirectX::XMVectorSet(0, 1, 0, 0); // 法線ベクトル
	plane.distance = 0.0f; // 原点(0,0,0)からの距離

	// レイの初期値を設定
	ray.start = DirectX::XMVectorSet(viewProjection.eye.x, viewProjection.eye.y, viewProjection.eye.z, 0);
	ray.dir = DirectX::XMVectorSet(0, 0, 0, 0);
}

void Mouse::Update()
{
	//マウスの現在の座標を取得する
	GetCursorPos(&po);

	// 駒の移動処理
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

	// マウスとブロックの当たり判定
	std::ostringstream raystr;
	raystr << "lay.start("
		<< std::fixed << std::setprecision(2)
		<< ray.start.m128_f32[0] << ","
		<< ray.start.m128_f32[1] << ","
		<< ray.start.m128_f32[2] << ")";


	debugText_->Print(raystr.str(), 50, 180, 1.0f);

	// レイと平面の当たり判定
	XMVECTOR inter;
	float distance;
	bool hit = Collision::CheckRay2Plane(ray, plane, &distance, &inter);
	if (hit) {
		debugText_->Print("HIT", 50, 260, 1.0f);
		// stringstreamをリセットし、交点座標を埋め込む
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