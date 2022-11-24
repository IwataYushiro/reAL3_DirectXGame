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
	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//テストモデル
	model_ = Model::CreateFromOBJ("cube", true);

	//クリックフラグ
	mouseClick_ = false;

	// 平面の初期値を設定
	plane.normal = DirectX::XMVectorSet(0, 1, 0, 0); // 法線ベクトル
	plane.distance = 0.0f; // 原点(0,0,0)からの距離

	// レイの初期値を設定
	ray.start = DirectX::XMVectorSet(viewProjection.eye.x, viewProjection.eye.y, viewProjection.eye.z, 0);
	ray.dir = DirectX::XMVectorSet(0, 0, 0, 0);

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,0 };
}

void Mouse::Update(ViewProjection& viewProjection)
{
	//マウスの現在の座標を取得する
	GetCursorPos(&po);
	HWND h = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(h, &po);

	// マウスのベクトルの初期化
	worldPo = { (float)po.x,(float)po.y,1 };

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

	// マウスのスクリーン座標をワールド座標に変換
	Matrix4 matInverseProjection = Matrix4Inverse(viewProjection.matProjection);
	Matrix4 matInverseView = Matrix4Inverse(viewProjection.matView);
	Matrix4 matInverseViewport = Matrix4Inverse(Viewport(1280, 720));

	Matrix4 matInverse = matInverseViewport * matInverseProjection * matInverseView;

	//W除算
	DivWorldPo = Vector3TransformCoord(worldPo, matInverse);

	//カメラからマウスへのベクトル
	vecPo = Vector3(viewProjection.eye.x - DivWorldPo.x,
		viewProjection.eye.y - DivWorldPo.y, viewProjection.eye.z - DivWorldPo.z);

	//正規化
	norVecPo = vecPo.normalize();

	//dirに代入
	ray.dir = DirectX::XMVectorSet(norVecPo.x, norVecPo.y, norVecPo.z, 0);

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

	// 行列更新
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