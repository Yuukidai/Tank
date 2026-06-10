#pragma once
#include "Engine//GameObject.h"
class Tank :
    public GameObject
{
public:
	Tank(GameObject* parent);
	~Tank();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
private:
	int hModel_;//タンクモデル
	int camType_;//カメラの種類
};

