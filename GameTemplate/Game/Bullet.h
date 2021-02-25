#pragma once
class Bullet : public IGameObject
{
	~Bullet();
	bool Start();
	void Update();
	
public:

	Vector3 m_position;
	Vector3 m_moveDirection = { 0.0f,0.0f,0.0f };
	float m_velocity = 1.0f;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CPointLight* m_pointLight = nullptr;
	int m_liveCount = 0;
};
