#pragma once

class GameOption;
class TitleScene:public IGameObject
{
private:
	bool Start() override;
	void Update() override;
	~TitleScene();

	prefab::CSkinModelRender* m_BG_ModelRender = nullptr;
	prefab::CPointLight* m_BGLight = nullptr;
	prefab::CSpriteRender* m_Monitor_SpriteRender = nullptr;
	prefab::CSpriteRender* m_MonitorLine_SpriteRender = nullptr;
	prefab::CSpriteRender* m_Rogo_SpriteRender = nullptr;
	prefab::CSpriteRender* m_Option_SpriteRender = nullptr;
	prefab::CSpriteRender* m_Start_SpriteRender = nullptr;
	prefab::CSpriteRender* m_Exit_SpriteRender = nullptr;
	prefab::CSpriteRender* m_Arrow_SpriteRender = nullptr;

	Vector4 m_semitrans = { 1, 1, 1, 0.7f };//半透明
	Vector3 m_smallScale = { 0.7f,0.7f,1.0f };//上下のメニューバーの拡大率
	//メニューバーの位置
	Vector3 m_topPos = { 440.0f,200.0f,0.0f };//上
	Vector3 m_centerPos = { 320.0f,0.0f,0.0f };//中
	Vector3 m_bottomPos = { 440.0f,-200.0f,0.0f };//下

	//オプション画面
	GameOption* m_option = nullptr;

	//BGM
	prefab::CSoundSource* ssBGM = nullptr;
	
	void CommandMove();
	void CommandSelectMove();

	//コマンドの種類
	enum TitleCommand {
		TC_Start,
		TC_Option,
		TC_Exit
	};
	TitleCommand m_titleCommand = TC_Start;		//現在選択中のコマンド
	bool m_selectFlag = false;					//コマンド決定済？
	bool m_selectMoveFlag = false;				//コマンド移動中？
	bool m_comandUpDown = false;				//false:上 true:下

	int m_commandTimer = 0;

};

