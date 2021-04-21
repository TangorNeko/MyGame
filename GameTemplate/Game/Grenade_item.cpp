#include "stdafx.h"
#include "Grenade_item.h"
#include "Flash.h"
Grenade_item::~Grenade_item()
{
	DeleteGO(m_skinModelRender);
}
bool Grenade_item::Start()
{
	//モデルを作成
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/Grenade.tkm");
	//m_skinModelRender->SetScale({ 5.0f, 5.0f, 5.0f });
	m_collider.SetStartPoint(m_position);
	topPos = m_position;
	topPos.y += 50;
	m_collider.SetEndPoint(topPos);
	m_collider.SetRadius(15.0f);
	//m_skinModelRender->SetPosition(m_position);

	m_gameScene = FindGO<GameScene>("gamescene");

	return true;
}
void Grenade_item::Update()
{
	if (m_gameScene->GetGameEndFlag() == true)
	{
		DeleteGO(this);
	}

	//各プレイヤーを検索
	QueryGOs<Character_base>("Player", [this](Character_base* player)->bool
		{
			//プレイヤーが近ければ
			
			if (player->m_collider.isHitCapsule(m_collider))
			{
				Flash* flash=NewGO<Flash>(0);
				flash->m_affectPlayerNum = player->m_enemy->m_playerNum;
				DeleteGO(this);				
			}
			return true;
		});
	ItemMotion();
	
}