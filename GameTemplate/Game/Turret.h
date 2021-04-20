#pragma once
class Turret
{
	~Turret();
	bool Start();
	void Update();
public:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;

	Vector3 m_position;
	Vector3 m_scale;
	Vector3 diff;
	Quaternion m_rot;

	bool m_CharacterOn = false;//キャラが上に乗っているか

};

