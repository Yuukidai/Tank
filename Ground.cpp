#include "Ground.h"
#include "Engine/Model.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent,"Ground"),hModel_(-1)
{

}

Ground::~Ground()//デストラクタ何もしない（オブジェクトが削除されるときに呼ばれる関数）
{
}

void Ground::Initialize()
{
	hModel_ = Model::Load("Ground.fbx");
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ground::Release()
{
}
