#include "stdafx.h"
#include "CSkinModelRender.h"

namespace prefab
{
	/// <summary>
	/// モデルの初期化関数。
	/// </summary>
	/// <param name="modelPath">モデルファイルのパス(.tkm)</param>
	/// <param name="skeletonPath">スケルトンファイルのパス(.tks)</param>
	/// <param name="buffer">ライトの定数バッファ</param>
	void CSkinModelRender::Init(const char* modelPath, const char* skeletonPath,void* data)
	{
		m_skeleton.Init(skeletonPath);

		ModelInitData initData;

		initData.m_tkmFilePath = modelPath;

		initData.m_fxFilePath = "Assets/shader/model.fx";

		//initData.m_vsEntryPointFunc = "VSMain";

		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		initData.m_skeleton = &m_skeleton;

		//TODO:引数にして利用者に入力させる必要がありそう。
		initData.m_modelUpAxis = enModelUpAxisZ;

		if (data != nullptr)
		{
			//定数バッファ周りテスト
			//WARNING:ここに固定の数値を入れるのは危険　sizeを知る仕組みが必要
			initData.m_expandConstantBufferSize = 28;

			initData.m_expandConstantBuffer = data;
		}

		m_model.Init(initData);
	}

	//モデルパスだけ版。コピーしてきただけ
	void CSkinModelRender::Init(const char* modelPath)
	{
		ModelInitData initData;

		initData.m_tkmFilePath = modelPath;

		initData.m_fxFilePath = "Assets/shader/model.fx";

		//initData.m_vsEntryPointFunc = "VSMain";

		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		//TODO:引数にして利用者に入力させる必要がありそう。
		initData.m_modelUpAxis = enModelUpAxisZ;

		m_model.Init(initData);
	}

	//TODO:モデルの描画っぽい、Updateのように毎フレーム呼ばれているようだが詳細がわからない
	void CSkinModelRender::Render(RenderContext& rc)
	{
		m_model.Draw(rc);
	}

	/// <summary>
	/// モデルの情報を更新する。
	/// </summary>
	void CSkinModelRender::UpdateModel()
	{
		m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
		m_skeleton.Update(m_model.GetWorldMatrix());
	}

	/// <summary>
	/// モデルの座標を設定する。
	/// </summary>
	/// <param name="pos">座標(Vector3)</param>
	void CSkinModelRender::SetPosition(Vector3 pos)
	{
		m_position = pos;

		UpdateModel();
	}

	/// <summary>
	/// モデルの回転を設定する。
	/// </summary>
	/// <param name="qRot">回転(Quaternion)</param>
	void CSkinModelRender::SetRotation(Quaternion qRot)
	{
		m_qRot = qRot;

		UpdateModel();
	}

	/// <summary>
	/// モデルの拡大率を設定する。
	/// </summary>
	/// <param name="scale">拡大率(Vector3)</param>
	void CSkinModelRender::SetScale(Vector3 scale)
	{
		m_scale = scale;

		UpdateModel();
	}
}