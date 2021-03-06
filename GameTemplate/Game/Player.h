#pragma once
#include "MyCapsuleCollider.h"
#include "TriangleCollider.h"

class BackGround;
class Debris;
class Bomb;
class MobiusGauge;
class GameScene;

class Player : public IGameObject
{
public:
	Player();
	~Player();
private:
	bool Start() override;
	void Update() override;


	//開始前カメラ移動
	void OpeningCamera();

	//体力、メビウスゲージの表示
	void DisplayStatus();

	//移動
	void Move();

	//攻撃
	void Attack();

	//必殺技
	void SpecialAttack();

	//爆弾を投げる
	void ThrowBomb();

	//保持しているガレキを浮遊させる。
	void HoldDebris();

	//保持している爆弾を浮遊させる。
	void HoldBomb();

	//磁力バーストを使用していない時の通常の動き
	void MagneticBehavior();

	//磁力バースト
	void MagneticBurst();

	//磁力の変化
	void ChangeMagnetPower();

	//カメラの移動
	void Camera();

	//当たり判定
	void Collision();

	//攻撃状態に切り替えできたら切り替える。
	void TryChangeStatusAttack();

	//特殊攻撃状態に切り替える
	void TryChangeStatusSpecialAttack();

	//バースト状態に切り替える
	void TryChangeStatusBurst();

	//走り状態に切り替えできたら切り替える。
	void TryChangeStatusRun();

	//歩き状態に切り替えできたら切り替える。
	void TryChangeStatusWalk();

	//落下状態に切り替える
	void TryChangeStatusFall();

	//待機状態に切り替えできたら切り替える。
	void TryChangeStatusIdle();

	//被弾状態に切り替える
	void TryChangeStatusHit();

	//アニメーションの状態更新
	void UpdateState();

	//アニメーションを再生
	void AnimationSelect();

	//発射先の計算。
	bool GetShootPoint(Vector3& crossPoint);

	//ファイナルカメラ
	void FinalHit();

public:

	//自分の体力にダメージを与える
	void Damage(int damage);

	//勝利した時
	void Win();

	//敗北した時
	void Lose();

	//必殺技ゲージをチャージする。
	void ChargeSpecialAttackGauge(int charge);

	//ノックバックをする。
	void KnockBack();

public://リファクタリング中に作られた関数
	void SetDamageEffectFront(const Vector3& front)
	{
		m_damageEffectFront = front;
	}

	void SetKnockBackFlag(bool flag)
	{
		m_isKnockBack = flag;
	}

	bool GetGravityAttackFlag()
	{
		return m_isGravityBulletAttack;
	}

	void SetEnemy(Player* enemy)
	{
		m_enemy = enemy;
	}

	const Vector3& GetMagPosition()
	{
		return m_magPosition;
	}

	int GetPlayerNum()
	{
		return m_playerNum;
	}

	void SetPlayerNum(int playerNum)
	{
		m_playerNum = playerNum;
	}

	int GetMagnetState()
	{
		return m_magnetState;
	}

	void SetMagnetState(int magPower)
	{
		m_magnetState = magPower;
	}

	bool IsBurst()
	{
		return m_isBurst;
	}

	int GetHP()
	{
		return m_hp;
	}

	bool IsBulletHitCollider(const MyCapsuleCollider& bulletCollider)
	{
		return m_collider.isHitCapsule(bulletCollider);
	}

	void ExecuteCharacon(Vector3 moveSpeed)
	{
		m_charaCon.Execute(moveSpeed, 1.0f);
	}

	void ResetFall()
	{
		m_fallLoop = 0;
	}

	void SetSensitivity(float sensitivity)
	{
		m_sensitivity = sensitivity;
	}

	void SetCameraFront(const Vector3& front)
	{
		m_cameraFront = front;
	}

	const Vector3& GetCameraFront()
	{
		return m_cameraFront;
	}

	void SetToCameraDirection(const Vector3& direction)
	{
		m_toCameraDir = direction;
	}

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition()
	{
		return m_position;
	}

	void SetMoveAmount(const Vector3& moveAmount)
	{
		m_moveAmount = moveAmount;
	}

public:
	//アニメーションの数
	enum {
		enAnimationClip_Attack,
		enAnimationClip_Run,
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Move,
		enAnimationClip_Fall,
		enAnimationClip_SpecialAttack,
		enAnimationClip_Burst,
		enAnimationClip_Hit,
		enAnimationClip_Death,
		enAnimationClip_Winner,
		enAnimationClip_num,			//列挙内で使う要素の数を表すダミー
	};

	//状態の数
	enum EnStatus {
		enStatus_Attack,		//攻撃状態
		enStatus_Run,			//走り状態
		enStatus_Idle,			//待機状態
		enStatus_Walk,			//歩き状態
		enStatus_Move,			//移動アクション状態		
		enStatus_Fall,			//落下状態
		enStatus_SpecialAttack,	//必殺技状態
		enStatus_Burst,			//バースト状態
		enStatus_Hit,			//被弾状態		
		enStatus_Num,			//状態の数。
	};

public:
	//ガレキ、爆弾の操作系
	std::vector<Debris*> m_holdDebrisVector;//保持しているガレキが格納されるコンテナ
	float m_holdDebrisRotateDeg = 0;//保持しているガレキの回転角度

	std::vector<Bomb*> m_holdBombVector;//保持している爆弾が格納されるコンテナ
	int m_selectBombNo = 0;//選択している爆弾の番号

	//ファイナルヒット関連
	bool m_Lose = false;//負けたかどうか
	bool m_WinAnimOn = false;//勝者アニメーションを開始する
	int m_LoseCameraLoop = 0;//ファイナルヒットカメラのループカウント
	bool m_FirstTime = true;//最初の一度だけ
	int m_loserNum = 0;//敗者のプレイヤー番号
	int m_LastCameraStatus = 0;//状態遷移番号
	float m_coef = 0.0f;//ベクターに掛ける値(coefficient)
	Vector3 m_LastFrontDir;//キャラが最後に向いた向き
	Vector3 m_winnerVec;//敗者から勝者に向かうベクトル
	Vector3 m_winnerWaistPos;//勝者の腰の位置

	prefab::CFontRender* m_bulletNumFont = nullptr;//残弾数
	prefab::CFontRender* m_bulletMaxFont = nullptr;//残弾数
private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//キャラクターのモデル
	prefab::CSpriteRender* m_crosshairRender = nullptr;			//照準のスプライト
	prefab::CSpotLight* m_spotLight = nullptr;					//プレイヤーを後ろから照らすライト

	int m_playerNum = -1;										//プレイヤーの番号 1P(0)、2P(1)
	int m_magnetState = -1;										//磁力、引力状態(-1)、斥力(1)
	int m_hp = 1000;											//体力
	float m_magnetCharge = 1000;								//磁力ゲージの現在の量

	Vector3 m_position = { 0.0f,0.0f,0.0f };					//キャラクターの座標
	Vector3 m_magPosition = { 0.0f,0.0f,0.0f };					//磁力が出ている地点
	Quaternion m_rot;											//キャラクターの回転
	Vector3 m_scale = { 0.8f, 0.8f, 0.8f };						//キャラクターの拡大率 **定数化**

	CharacterController m_charaCon;								//プレイヤーのキャラコン
	Vector3 m_moveAmount = { 0.0f,0.0f,0.0f };					//キャラコンに実行させる移動量
	int m_fallLoop = 0;											//落下制御用のループカウント
	float m_characterSpeed = 6.0;								//キャラクターの移動速度

	Vector3 m_toCameraDir = { 0.0f,0.0f,-1.0f };				//プレイヤーからカメラへの向き
	Vector3 m_cameraFront;										//カメラの前方向
	Vector3 m_cameraRight;										//カメラの右方向
	Vector3 m_cameraPos;										//カメラのポジション
	Quaternion m_cameraQRotY;									//プレイヤーカメラのY軸の回転
	float m_sensitivity = 2.0f;									//視点感度
	bool m_isLockon = false;									//カメラロックオンしているか。


	BackGround* m_stageModel = nullptr;							//背景のモデル(当たり判定用)
	TriangleCollider m_triCollider[2];							//単純な三角形の当たり判定(発射先の判定に使う)
	MyCapsuleCollider m_collider;								//カプセル状の当たり判定(弾の当たり判定に使う)
	
	bool m_isBurst = false;										//バーストしているか。
	int m_burstCount = 0;										//バーストを使用してからの経過フレーム
	bool m_isAttacking = false;									//攻撃を発射しているか。
	int m_attackCount = 0;										//攻撃を発射してからの経過フレーム(隙)
	bool m_isSteal = false;										//一回の引力バースト中にすでに敵の弾を奪ったか

	//アニメーション関連
	AnimationClip animationClips[enAnimationClip_num];			//アニメーションクリップ
	EnStatus m_animStatus = enStatus_Idle;						//現在のアニメーションの状態
	bool m_SpecialAttackOn = false;								//アニメーション用フラグ
	bool m_HitOn = false;										//被弾したかどうか

	//必殺技関連
	int m_specialShotFlag = false;								//必殺技を発射中?
	int m_specialShotCount = 0;									//必殺技を発射し始めてからの経過フレーム
	int m_specialAttackGauge = 0;								//必殺技のゲージ量
	int m_oldSpecialAttackGauge = 0;							//1フレーム前の必殺技ゲージ量
	bool m_isGravityBulletAttack = false;						//引力の必殺技の攻撃タイミングを指示する用変数。

	//ノックバック関連
	bool m_isKnockBack = false;									//ノックバック状態?
	int m_isknockBackCount = 0;									//ノックバックし始めてからの経過フレーム

	//体力等の情報表示
	prefab::CSpriteRender* m_HPBarSpriteRender = nullptr;		//HPバーのスプライト
	prefab::CSpriteRender* m_HPBarDarkSpriteRender = nullptr;	//HPバーの黒い(体力がなくなった)部分のスプライト
	prefab::CSpriteRender* m_DamageBarSpriteRender = nullptr;	//受けたダメージ分のHPバーのスプライト
	bool m_hpBarRedFlag = false;								//HPバーを赤くするか
	MobiusGauge* m_mobiusGauge = nullptr;						//メビウスゲージ
	prefab::CFontRender* m_chargeSPFontRender = nullptr;		//必殺技ゲージの溜まり具合のフォント

	//エフェクト
	prefab::CEffect* m_magEffect[2] = { nullptr,nullptr };		//磁力のエフェクト　2つのエフェクトを連続で再生し続ける。
	int m_magEffectCallCount = 41;								//磁力エフェクトを呼ぶまでの時間
	prefab::CEffect* m_burstEffect = nullptr;					//磁力バーストのエフェクト
	prefab::CEffect* m_hitEffect = nullptr;						//ダメージエフェクト
	Vector3 m_damageEffectFront = { 0.0f,0.0f,0.0f };			//ダメージを食らった方向　エフェクトをダメージが食らった向きに
	prefab::CEffect* m_SPFireEffect = nullptr;						//必殺技の発射エフェクト
	prefab::CEffect* m_SPGaugeMaxEffect = nullptr;				//必殺ゲージが最大まで溜まった時に出るエフェクト
	prefab::CEffect* m_SPChargeEffectRed = nullptr;				//必殺技を放つ溜め動作のときのエフェクト　斥力
	prefab::CEffect* m_SPChargeEffectBlue = nullptr;			//必殺技を放つ溜め動作のときのエフェクト　引力

	//音
	int m_footstepsTimer = 0;									//足音の鳴る間隔をカウントする

	//勝敗表示
	prefab::CSpriteRender* m_resultWinnerSprite = nullptr;		//勝者を表示するスプライト(○P)
	prefab::CSpriteRender* m_resultWinSprite = nullptr;			//勝利のスプライト(WIN!)

	GameScene* m_gameScene = nullptr;							//ゲームシーン
	Player* m_enemy = nullptr;									//敵プレイヤー




	//後から分離したい
	Vector3 m_sequenceCameraPos;//シーケンスカメラの座標
	Vector3 m_targetPos = { 0.0f,0.0f,0.0f }; //  **定数化**
	float m_openingCameraGainSpeed = 10;//カメラとターゲットとの接近速度	
	float m_openingCameraRotationRad = 0.0f;//オープニングカメラの回転角度
	int m_openingCameraCount = 0;//オープニングカメラが始まってからの経過フレーム
};



