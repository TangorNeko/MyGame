#include "stdafx.h"
#include "system/system.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"
#include "TransitionGenerator.h"
#include "GameOption.h"

namespace
{
	const Vector3 LIGHTCAMERA_POSITION = { 500.0f,500.0f,-500.0f };
	const Vector3 LIGHTCAMERA_TARGET = { 0.0f,0.0f,0.0f };
	const Vector3 LIGHTCAMERA_UP = { 1.0f,0.0f,0.0f };
	const float LIGHTCAMERA_WIDTH = 2000.0f;
	const float LIGHTCAMERA_HEIGHT = 2000.0f;
}

void PreLoad();
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//2画面描画モードはOFFから始める。
	GameObjectManager::GetInstance()->Set2ScreenMode(false);

	//ライトマネージャーのインスタンスを作成
	CLightManager::CreateInstance();
	CLightManager::GetInstance()->SetLightCameraPosition(LIGHTCAMERA_POSITION);
	CLightManager::GetInstance()->SetLightCameraTarget(LIGHTCAMERA_TARGET);
	CLightManager::GetInstance()->SetLightCameraUp(LIGHTCAMERA_UP);
	CLightManager::GetInstance()->SetLightCameraUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	CLightManager::GetInstance()->SetLightCameraWidth(LIGHTCAMERA_WIDTH);
	CLightManager::GetInstance()->SetLightCameraHeight(LIGHTCAMERA_HEIGHT);

	//リソースマネージャのインスタンスを作成
	ResourceBankManager::CreateInstance();

	CSoundEngine::CreateInstance();
	CSoundEngine::GetInstance()->Init();

	EffectEngine::CreateInstance();

	PostEffectManager::CreateInstance();
	//ブルームフラグ、シャドウフラグの順番
	PostEffectManager::GetInstance()->Init(true,true);
	//////////////////////////////////////////////////
	
	//FPS固定用ストップウォッチ
	Stopwatch stopwatch;

	//モデルデータ、エフェクトデータの事前ロード。
	PreLoad();

	//ゲーム設定の読み込み
	GameOption::ReadOption();

	TransitionGenerator* tg = NewGO<TransitionGenerator>(5, "TransitionGenerator");

	//トランジション
	TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::Circle, TRANSITION_TIME_NORMAL, false);

	//タイトルシーンを作成。
	TitleScene* title = NewGO<TitleScene>(6, "titlescene");

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//FPS計測用ストップウォッチの計測開始
		stopwatch.Start();

		//レンダリング開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		GameObjectManager::GetInstance()->ExecuteUpdate();

		//Renderはモデル等、エフェクトを受けるものを描画する
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//PostRenderはスプライト、フォント等、エフェクトを受けないものを描画する
		GameObjectManager::GetInstance()->ExecutePostRender(renderContext);

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();

		//スピンロックを行う。
		int restTime = 0;
		do {
			stopwatch.Stop();
			restTime = 16 - (int)stopwatch.GetElapsedMillisecond();
		} while (restTime > 0);


		//ストップウォッチの計測終了
		stopwatch.Stop();
		//デルタタイムをストップウォッチの計測時間から、計算する
		GameTime::GetInstance().PushFrameDeltaTime((float)stopwatch.GetElapsed());
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();

	//ライトマネージャーを削除
	CLightManager::DeleteInstance();
	
	//tkmFileManagerを削除
	ResourceBankManager::DeleteInstance();

	//サウンドエンジンを削除
	CSoundEngine::DeleteInstance();
	
	//ポストエフェクトマネージャーを削除
	PostEffectManager::DeleteInstance();
	return 0;
}

//使用するモデル、エフェクトの事前ロード、
//TODO:後からcsvファイル等にまとめて連想配列などで使用できるようにしたいが...
void PreLoad()
{
	//モデルの事前ロード
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/Player1.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/Player2.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/TitleCylinder.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/pipe.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/gear.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/neji.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/KnightBullet.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/Gravity.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/repulsion.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/stage00.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/SkyBoard.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/Grenade.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/FlashGrenade.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/SmokeGrenade.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/scrap.tkm");
	prefab::CSkinModelRender::PreLoadModel("Assets/modelData/Gravity2.tkm");

	//エフェクトの事前ロード
	prefab::CEffect::PreLoadEffect(u"Assets/effect/閃光.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/爆発.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/引力弾.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/引力弾2.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/Blackhole3.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/焼夷.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/斥力.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/引力.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/ダメージ.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/キュピーン.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/斥力チャージ.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/引力チャージ.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/引力弾発射.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/斥力弾発射.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/引力バースト.efk");
	prefab::CEffect::PreLoadEffect(u"Assets/effect/斥力バースト.efk");
}
