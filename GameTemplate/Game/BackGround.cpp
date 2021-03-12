#include "stdafx.h"
#include "BackGround.h"

BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
}

bool BackGround::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);

	/*
	m_pLig = NewGO<prefab::CPointLight>(0);
	m_pLig->SetPosition({ 100.0f,0.0f,0.0f });
	m_pLig->SetColor({ 1.0f,1.0f,1.0f });
	m_pLig->SetRange(500);
	*/

	m_skinModelRender->Init("Assets/modelData/protostage.tkm");

	m_physicsStaticObject.CreateFromModel(m_skinModelRender->GetModel(), m_skinModelRender->GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update()
{
	m_skinModelRender->SetPosition(m_position);
}