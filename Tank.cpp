#include "Tank.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"

namespace
{
	XMVECTOR vFront = { 0 ,0, 1, 0 };//戦車の前ベクトル
	const float moveSpeed = 0.1f;
	enum CAM_TYPE
	{
		FIXED_CAM,//固定カメラ
		TPS_CAM,//三人称視点
		TPS_CAMROT,//三人称視点カメラ回転付き
		FPS_CAM,//一人称視点
		CAM_TYPE_MAX//
	};
}


Tank::Tank(GameObject* parent)
	:GameObject(parent,"Tank"),hModel_(-1),camType_(FIXED_CAM)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
}

void Tank::Update()
{
	if (Input::IsKey(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;//0,1,2の順でCAM_TYPE_MAX-1のじゅんで切り替えていく
	}
	switch (camType_)
	{
		case FIXED_CAM:
			break;
		case TPS_CAM:
			break;
		case TPS_CAMROT:
			break;
		case FPS_CAM:
			break;
	}

	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.0f;
	}

	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.0f;
	}
	Debug::Log("CAMTYPE =");
	Debug::Log(camType_, true);

	if (Input::IsKey(DIK_W))
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸に回転行列を作る
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);

		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos); //ストア;書き込み、格納
	}

	//レイキャストして浮いてたら地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は0より下に彫られて作れられている。そうじゃない時はもっと上から
	data.dir = { 0, -1, 0 };//真下にれいをとばす

	Ground* pGround = (Ground*)FindObject("Ground");
	int hGroundModel = pGround->GetModelHandle();
	Model::RayCast(hGroundModel, &data);

	if (data.hit == true)
	{
		transform_.position_.y = - data.dist;
	}

	if (Input::IsKey(DIK_S))
	{

	}


}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

void Tank::Release()
{
}
