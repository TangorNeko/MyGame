#include "stdafx.h"
#include "SampleScene.h"

#include "Player.h"
#include "BackGround.h"
#include "SkyBoard.h"
#include "Debris.h"
#include "DebrisBlock.h"

SampleScene::~SampleScene()
{
	DeleteGO(m_stageLight);
	DeleteGO(m_backGround);
	DeleteGO(m_sky);
	DeleteGO(m_player1);
	DeleteGO(m_player2);
}

bool SampleScene::Start()
{
	//�X�e�[�W�̃��C�g���쐬
	m_stageLight = NewGO<prefab::CDirectionLight>(0);
	m_stageLight->SetDirection({ 0.0f,-1.0f,0.0f });
	m_stageLight->SetColor({ 0.5f,0.5f,0.5f });

	m_player1 = NewGO<Player>(0, "Player");
	m_player1->m_position = { 0.0f,0.0f,-500.0f };
	m_player1->m_playerNum = 0;
	m_player1->m_magPower = 1;

	m_player2 = NewGO<Player>(0, "Player");
	m_player2->m_position = { 0.0f,0.0f,500.0f };
	m_player2->m_playerNum = 1;
	m_player2->m_magPower = -1;

	//�e�v���C���[�ɓG��n��
	m_player2->m_enemy = m_player1;
	m_player1->m_enemy = m_player2;

	//�X�e�[�W�̕\��
	m_backGround = NewGO<BackGround>(0, "background");

	//�K���L�u���b�N�B
	DebrisBlock* debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -870.0f,160.0f,535.0f };

	debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -820.0f,160.0f,535.0f };

	debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -870.0f,160.0f,485.0f };

	debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -820.0f,160.0f,485.0f };


	debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -870.0f,160.0f,-535.0f };

	debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -820.0f,160.0f,-535.0f };

	debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -870.0f,160.0f,-485.0f };

	debrisblock = NewGO<DebrisBlock>(0, "debrisblock");
	debrisblock->m_position = { -820.0f,160.0f,-485.0f };

	//�K���L�B
	Debris* debris = NewGO<Debris>(0, "debris");
	debris->m_debrisState = Debris::enDrop;
	debris->m_position = { 0.0f,0.0f,0.0f };

	debris = NewGO<Debris>(0, "debris");
	debris->m_debrisState = Debris::enDrop;
	debris->m_debrisShape = Debris::enSword;
	debris->m_position = { 200.0f,0.0f,0.0f };

	debris = NewGO<Debris>(0, "debris");
	debris->m_debrisState = Debris::enDrop;
	debris->m_position = { 300.0f,0.0f,0.0f };

	debris = NewGO<Debris>(0, "debris");
	debris->m_debrisState = Debris::enDrop;
	debris->m_position = { 300.0f,0.0f,100.0f };

	//����쐬�B�L���[�u�}�b�v����Ȃ��Ă����̔|���B
	m_sky = NewGO<SkyBoard>(0);

	//���ׂč쐬���I���������2��ʂɂ���B
	GameObjectManager::GetInstance()->Set2ScreenMode(true);

	return true;
}

void SampleScene::Update()
{

}