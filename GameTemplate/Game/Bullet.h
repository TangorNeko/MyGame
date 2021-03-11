#pragma once
class ShowModel;

class Bullet : public IGameObject
{
	~Bullet();
	bool Start();
	void Update();
	
public:

	Vector3 m_position;
	Vector3 m_moveDirection = { 0.0f,0.0f,0.0f };
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	float m_velocity = 1.0f;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;

	prefab::CSkinModelRender* m_oldbullet = nullptr;
	prefab::CPointLight* m_pointLight = nullptr;
	int m_liveCount = 0;
	int m_parentNo = 0;
	bool m_isAffectedFromEnemyPower = false;
};

