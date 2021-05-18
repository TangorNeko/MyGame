#include "stdafx.h"
#include "Bomb.h"

#include "Player.h"
#include "BackGround.h"

#include "Explosion.h"
#include "Flash.h"
#include "Incendia.h"
Bomb::~Bomb()
{
	DeleteGO(m_skinModelRender);
}

bool Bomb::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);

	//���e�̌`��œǂݍ��ރ��f���𕪊�
	switch (m_bombShape)
	{
	case enGrenade:
		m_skinModelRender->Init("Assets/modelData/FlashGrenade.tkm");
		m_skinModelRender->SetScale({ 0.5f, 0.5f, 0.5f });
		//������p�x��������ɂ���B
		m_moveDirection.y += 0.4f;
		m_moveDirection.Normalize();
		break;
	case enFlashGrenade:
		m_skinModelRender->Init("Assets/modelData/MageBullet.tkm");
		m_skinModelRender->SetScale({ 0.5f, 0.5f, 0.5f });
		//������p�x��������ɂ���B
		m_moveDirection.y += 0.4f;
		m_moveDirection.Normalize();
		break;
	case enIncendiaryGrenade:
		m_skinModelRender->Init("Assets/modelData/KnightBullet.tkm");
		m_skinModelRender->SetScale({ 0.5f, 0.5f, 0.5f });
		//������p�x��������ɂ���B
		m_moveDirection.y += 0.4f;
		m_moveDirection.Normalize();
		break;
	default:
		MessageBoxA(nullptr, "���݂��Ȃ����e�̌`��ł��B\n", "�G���[", MB_OK);
		break;
	}

	//�X�e�[�W�Ƃ̓����蔻��p
	m_stageModel = FindGO<BackGround>("background");

	return true;
}

void Bomb::Update()
{
	//�O�t���[���̍��W���L�^
	m_oldPosition = m_position;

	//���e�̏�Ԃŕ���
	switch (m_bombState)
	{
	case enDrop:
		//�n�ʂɗ����Ă��鎞�̋���
		AsDropBehave();
		break;
	case enBullet:
		//�e�Ƃ��Ĕ��˂���Ă��鎞�̋���
		AsBulletBehave();
		break;
	case enHold:
		//�v���C���[�ɕێ�����Ă��鎞�̋���
		AsHoldBehave();
		break;
	case enPop:
		//�����ɓ�����������̋���
		AsPopBehave();
		break;
	default:
		MessageBoxA(nullptr, "���݂��Ȃ����e�̏�Ԃł��B", "�G���[", MB_OK);
		break;
	}

	m_skinModelRender->SetPosition(m_position);

	//Bomb�����ɗ��������A�����B
	if (m_position.y <= -1000.0f) {
		DeleteGO(this);
	}
}


//�n�ʂɗ����Ă��鎞�̋���
void Bomb::AsDropBehave()
{
	QueryGOs<Player>("Player", [this](Player* player)->bool {

		Vector3 toPlayer = player->m_position - m_position;

		//���͂̎��̂�
		if (player->m_magPower == -1)
		{
			//�o�[�X�g���Ă�����������Ă���
			if (toPlayer.Length() > 50 && toPlayer.Length() < 500.0f && player->m_isBurst == true)
			{
				toPlayer.y += 10.0f;
				Vector3 moveDir = toPlayer;
				moveDir.Normalize();

				//x�Az���ꂼ��ʁX�ő���
				m_position.x += moveDir.x *= 30.0f;
				//�ǂɂԂ������Ƃ�
				Vector3 crossPoint;
				bool isHit = m_stageModel->isLineHitModel(m_oldPosition, m_position, crossPoint);
				if (isHit == true) {
					m_position = m_oldPosition;
				}
				else
					m_oldPosition = m_position;

				m_position.z += moveDir.z *= 30.0f;
				//�ǂɂԂ������Ƃ�
				isHit = m_stageModel->isLineHitModel(m_oldPosition, m_position, crossPoint);
				if (isHit == true) {
					m_position = m_oldPosition;
				}
				else
					m_oldPosition = m_position;
			}

			//�߂��ɒe�������3���ȓ��Ȃ�E����
			if (toPlayer.Length() < 100.0f && player->m_holdBombVector.size() < 3)
			{
				m_parent = player;
				m_bombState = enHold;

				//�v���C���[�̕ێ����锚�e�R���e�i�Ɋi�[
				player->m_holdBombVector.push_back(this);
				//�v���C���[���I�����Ă��锚�e�����Z�b�g�B
				player->m_selectBombNo = 0;
			}
		}

		//�˗͂̎�
		if (player->m_magPower == 1)
		{
			//�o�[�X�g���Ă�����������Ă���
			if (toPlayer.Length() > 50 && toPlayer.Length() < 500.0f && player->m_isBurst == true)
			{
				Vector3 moveDir = toPlayer;
				moveDir.y = 0.0f;
				moveDir.Normalize();

				//x�Az���ꂼ��ʁX�ő���
				m_position.x += moveDir.x *= -30.0f;
				//�ǂɂԂ������Ƃ�
				Vector3 crossPoint;
				bool isHit = m_stageModel->isLineHitModel(m_oldPosition, m_position, crossPoint);
				if (isHit == true) {
					m_position = m_oldPosition;
				}
				else
					m_oldPosition = m_position;

				m_position.z += moveDir.z *= -30.0f;
				//�ǂɂԂ������Ƃ�
				isHit = m_stageModel->isLineHitModel(m_oldPosition, m_position, crossPoint);
				if (isHit == true) {
					m_position = m_oldPosition;
				}
				else
					m_oldPosition = m_position;

				m_position.y += 10.0f;
			}

		}
		return true;
		});
	//�d�͏���
	m_position.y -= 5.0f;
	Vector3 crossPoint;
	bool isHit = m_stageModel->isLineHitModel(m_oldPosition, m_position, crossPoint);
	if (isHit == true)
	{
		m_position = m_oldPosition;
	}
}

//�e�Ƃ��Ĕ��˂���Ă��鎞�̋���
void Bomb::AsBulletBehave()
{
	//�v���C���[�Ƃ̓����蔻��p
	m_bulletCollider.SetStartPoint(m_oldPosition);
	m_bulletCollider.SetRadius(60.0f);

	QueryGOs<Player>("Player", [this](Player* player)->bool
		{
			//���˂����v���C���[�ƈႤ��
			if (player->m_playerNum != m_parent->m_playerNum)
			{
				//�G�v���C���[�����̓o�[�X�g���Ă��鎞
				if (player->m_isBurst == true)
				{
					Vector3 toPlayer = player->m_magPosition - m_position;

					//�G�Ƃ̋�����500�����Ȃ�
					if (toPlayer.Length() < 500.0f)
					{						
						//���͂Ȃ�
						if (player->m_magPower == -1)
						{
							toPlayer.Normalize();
							Vector3 newDirection = m_moveDirection + toPlayer;
							newDirection /= 2;
							newDirection.Normalize();
							m_moveDirection = newDirection;
						}
						else //�˗͂Ȃ�
						{
							toPlayer.Normalize();
							Vector3 newDirection = m_moveDirection - toPlayer;
							newDirection /= 2;
							newDirection.Normalize();
							m_moveDirection = newDirection;
						}
					}
				}

				//�ړ�����(TODO:�������e�ƈႤ�v���C���[��1�l�������Ȃ��̂�1�񂵂��Ă΂�Ȃ��̂ő��v�����A�ꏊ�̈ړ��͌�������A
				//���̏ꍇ�AQueryGOs���ړ������Ɠ����蔻�菈����2��ɕ����Ă��邱�ƂɂȂ邩��)
				m_position += m_moveDirection * m_velocity * 0.5f;
				m_moveDirection.y -= 3.0f * 3.0f * 0.002f;
				m_moveDirection.Normalize();

				//�ړ���̓����蔻����X�V
				m_bulletCollider.SetEndPoint(m_position);

				//�����蔻��Ƀq�b�g���Ă���Ȃ�N���B
				if (player->m_collider.isHitCapsule(m_bulletCollider))
				{
					//��������������|�b�v������
					m_bombState = enPop;
				}
			}
			return true;
		});

	//�X�e�[�W�Ƃ̓����蔻��
	Vector3 crossPoint;
	bool isHit = m_stageModel->isLineHitModel(m_oldPosition, m_position, crossPoint);
	if (isHit == true)
	{
		m_position = crossPoint;

		Vector3 moveDir = m_position - m_oldPosition;
		moveDir.Normalize();

		//������������菭����O����|�b�v������
		m_position -= moveDir * 30.0f;

		m_bombState = enPop;
	}
}


//�v���C���[�ɕێ�����Ă��鎞�̋���
void Bomb::AsHoldBehave()
{
}

//�����ɓ�����������̋���
void Bomb::AsPopBehave()
{
	m_position.y -= 10.0f;

	//�X�e�[�W�Ƃ̓����蔻��
	Vector3 crossPoint;
	bool isHit = m_stageModel->isLineHitModel(m_oldPosition, m_position, crossPoint);
	if (isHit == true)
	{
		//�����������Ƀh���b�v������
		m_position = m_oldPosition;

		//���e�̎�ނɂ���ĕ���B
		switch(m_bombShape)
		{
			case enGrenade:
			m_explosionCount++;
			if (m_explosionCount >= 80) {
				Explosion* explosion = NewGO<Explosion>(0);
				explosion->m_position = crossPoint;
				DeleteGO(this);
			}
			break;
			case enFlashGrenade:
			m_explosionCount++;
			if (m_explosionCount >= 80) {
				Flash* flash = NewGO<Flash>(0);
				flash->m_position = crossPoint;
				flash->m_parentNum = m_parent->m_playerNum;
				DeleteGO(this);
			}
			break;
			case enIncendiaryGrenade:
			m_explosionCount++;
			if (m_explosionCount >= 80) {
				Incendia* incendia = NewGO<Incendia>(0);
				incendia->m_position = crossPoint;
				DeleteGO(this);
			}
			break;
		}
	}
}