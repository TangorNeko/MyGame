#include "stdafx.h"
#include "Character_base.h"
#include "Bullet.h"
#include "ChargeShot.h"
#include <string>

//Character_base::~Character_base()
//{
//	DeleteGO(m_skinModelRender);
//	DeleteGO(m_pointLight);
//	DeleteGO(m_fontRender);
//	DeleteGO(m_spriteRender);
//}

void Character_base::Collision()
{
	//三角形の当たり判定をつくる
	Vector3 sidePos1 = m_position;
	sidePos1.y += 60.0f;
	Vector3 diff = m_enemy->m_position - m_position;
	diff.Normalize();
	diff.Cross(Vector3::AxisY);
	Vector3 sidePos2 = sidePos1;
	sidePos1 += diff * 40;
	sidePos2 -= diff * 40;

	m_collider.SetVertex(m_position, sidePos1, sidePos2);
}

void Character_base::ChangeMagnetPower()
{
	m_timer++;
	if (m_timer == 600)
	{
		if (m_isMagPowerIncreasing)
		{
			if (m_magPower == 2)
			{
				m_magPower = 1;
				m_isMagPowerIncreasing = false;
			}
			else
			{
				m_magPower++;
			}
		}
		else
		{
			if (m_magPower == -2)
			{
				m_magPower = -1;
				m_isMagPowerIncreasing = true;
			}
			else
			{
				m_magPower--;
			}
		}
		m_timer = 0;
	}
}

void Character_base::DisplayStatus()
{
	//体力、チャージ、現在の自分の磁力の状態の表示
	std::wstring powerText;
	switch (m_magPower)
	{
	case -2:
		powerText = L"引力Lv2";
		m_fontRender->SetColor({ 0.0f,0.0f,1.0f,1.0f });
		break;
	case -1:
		powerText = L"引力Lv1";
		m_fontRender->SetColor({ 0.0f,0.5f,1.0f,1.0f });
		break;
	case 0:
		powerText = L"磁力なし";
		m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });
		break;
	case 1:
		powerText = L"斥力Lv1";
		m_fontRender->SetColor({ 1.0f,0.4f,0.4f,1.0f });
		break;
	case 2:
		powerText = L"斥力Lv2";
		m_fontRender->SetColor({ 1.0f,0.0f,0.0f,1.0f });
		break;
	default:
		powerText = L"error";
	}

	m_fontRender->SetText(L"HP:" + std::to_wstring(m_hp)
		+ L"\nCharge:" + std::to_wstring(m_charge / 10.0f)
		+ L"%\n\n\n\n\n\n\n\n\n\n\n\n\n磁力:" + powerText
		+ L"\n磁力の変化まで:" + std::to_wstring((600 - m_timer) / 60)
		+ L"　　　　　　　　  移動アクション:" + std::to_wstring(m_moveActionCount / 60));
}

void Character_base::MoveAction()
{
	//移動アクション
	if (g_pad[m_playerNum]->IsTrigger(enButtonA) && m_moveActionCount == 0 && !(g_pad[m_playerNum]->IsPress(enButtonLB2)))
	{
		m_skinModelRender->SetScale({ 0.0f,0.0f,0.0f });
		m_moveActionCount = 600;
		m_moveSpeed += m_characterDirection * 500.0f;
	}
	else
	{
		if (--m_moveActionCount <= 550)
		{
			m_skinModelRender->SetScale({ Scale });
		}

		if (m_moveActionCount < 0)
		{
			m_moveActionCount = 0;
		}
	}
}

void Character_base::NormalAttack()
{
	//通常攻撃
	if (--m_normalAttackCount < 0)
	{
		m_normalAttackCount = 0;
	}

	if (g_pad[m_playerNum]->IsTrigger(enButtonRB1) && m_normalAttackCount == 0)
	{
		if (m_isLock)
		{
			Bullet* bullet = NewGO<Bullet>(0, "bullet");
			bullet->m_position = m_position;
			bullet->m_position.y += 50;
			Vector3 dir = m_enemy->m_magPosition - m_magPosition;
			dir.Normalize();
			bullet->m_moveDirection = dir;
			bullet->m_velocity = 25.0f;
			bullet->m_parentNo = m_playerNum;
		}
		else
		{
			Bullet* bullet = NewGO<Bullet>(0, "bullet");
			bullet->m_position = m_position;
			bullet->m_position.y += 50;
			bullet->m_moveDirection = m_position - g_camera3D[m_playerNum]->GetPosition();
			bullet->m_moveDirection.y = 0.0f;
			bullet->m_moveDirection.Normalize();
			bullet->m_velocity = 25.0f;
			bullet->m_parentNo = m_playerNum;
		}

		m_normalAttackCount = 30;
	}
}

void Character_base::Charge()
{
	//チャージ
	if (g_pad[m_playerNum]->IsPress(enButtonLB2) && g_pad[m_playerNum]->IsPress(enButtonRB2))
	{
		m_charge += 10.0f - m_magPower * 2.5f;
		if (m_charge > 33.3f) {
			m_chargelevel = 1;
		}
		else if (m_charge > 66.6f) {
			m_chargelevel = 2;
		}
		else if (m_charge > 1000.0f)
		{
			m_chargelevel = 3;
			m_charge = 1000.0f;
		}
		else m_chargelevel = 0;

		m_moveSpeed = { 0.0f,0.0f,0.0f };
	}

	//チャージ確認用
	if (m_charge < 1000.0f) {
		m_pointLight->SetColor({ 0.0f,m_charge / 100,0.0f });
	}
	else
	{
		m_pointLight->SetColor({ 10.0f,0.0f,0.0f });
	}
	m_pointLight->SetPosition(m_position);
}



void Character_base::Camera()
{
	//カメラ関連
	if (g_pad[m_playerNum]->IsTrigger(enButtonRB3))
	{
		m_isLock = !m_isLock;//ロック切り替え
	}

	if (m_isLock)//ロックしているなら
	{

		Vector3 toCamera = m_position - m_enemy->m_position;//自分から敵へ向かうベクトル



		toCamera.Normalize();
		Vector3 Axis;
		Axis.Cross(toCamera, Vector3::Up);
		toCamera *= 140.0f;

		Quaternion qRot;
		qRot.SetRotationDeg(Axis, 45.0f);
		qRot.Apply(toCamera);


		g_camera3D[m_playerNum]->SetPosition(m_position + toCamera);
		g_camera3D[m_playerNum]->SetTarget(m_enemy->m_magPosition);
	}
	else
	{
		Vector3 targetPos = m_position;
		targetPos.y += 50.0f;

		Quaternion qRotY;
		qRotY.SetRotationDeg(Vector3::AxisY, g_pad[m_playerNum]->GetRStickXF() * 1.5);
		qRotY.Apply(m_toCamera);



		Quaternion qRotX;
		Vector3 right = g_camera3D[m_playerNum]->GetRight();
		qRotX.SetRotationDeg(right, g_pad[m_playerNum]->GetRStickYF() * -1.5);
		Vector3 checkToCamera = m_toCamera;
		qRotX.Apply(checkToCamera);
		checkToCamera.Normalize();
		float t = checkToCamera.Dot(Vector3::Up);
		if (t > 0.99f || t < 0.1f)
		{

		}
		else
		{
			qRotX.Apply(m_toCamera);
		}

		Vector3 cameraPos = m_position + m_toCamera;
		//g_camera3D->SetPosition(m_position + m_toCamera);
		g_camera3D[m_playerNum]->SetPosition(cameraPos);
		g_camera3D[m_playerNum]->SetTarget(targetPos);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//if (g_pad[m_playerNum]->IsTrigger(enButtonLB1))
		//{				
		//	Vector3 atarget = targetPos - m_position;//a
		//	Vector3 btarget = m_enemy->m_position - m_position;//b	
		//	atarget.Normalize();
		//	btarget.Normalize();
		//	float t=atarget.Dot(btarget);
		//	float angle = acosf(t);//アークコサイン
		//	if (atarget.x < 0) {
		//		angle *= -1;
		//	}

		//}

	}

}

void Character_base::Damage(int damage)
{
	m_hp -= damage;
	if (m_hp <= 0)
	{
		m_hp = 0;


		//WARNING:お互いに同タイミングに弾を発射してどちらもHP0になった時おそらくどちらも勝利しどちらも敗北する。
		Lose();
		m_isSceneStop = true;

		m_enemy->Win();
		m_enemy->m_isSceneStop = true;
	}

	//攻撃を受けたら移動アクションの残り時間が短縮される。
	m_moveActionCount -= 120;
	if (m_moveActionCount < 0)
	{
		m_moveActionCount = 0;
	}

}

void Character_base::Win()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(2);
	m_spriteRender->SetDrawScreen((prefab::CSpriteRender::DrawScreen)m_playerNum);
	m_spriteRender->Init("Assets/Image/Syouri.dds", 256, 256);
}

void Character_base::Lose()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(2);
	m_spriteRender->SetDrawScreen((prefab::CSpriteRender::DrawScreen)m_playerNum);
	m_spriteRender->Init("Assets/Image/Haiboku.dds", 256, 256);
}

void Character_base::PlayerMagneticMove()
{
	m_position_with_enemy = m_position - m_enemy->m_position;//自分から敵までの距離ベクトル
	if (m_position_with_enemy.Length() < 500) {//敵が前にいる状態かつ、距離が近ければ
		if (m_magPower >= 1 && m_enemy->m_magPower >= 1)//互いに斥力の状態
		{
			m_repulsionSpeed = m_position_with_enemy;//途中だよ
			//
		}
	}
	
}