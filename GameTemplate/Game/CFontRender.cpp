#include "stdafx.h"
#include "CFontRender.h"

namespace
{
	const float SPLITSCREEN_ASPECT_ADJUSTMENT_VALUE = 2.0f;
}

namespace prefab
{
	void CFontRender::PostRender(RenderContext& rc, Camera* camera)
	{
		if (rc.GetRenderStep() == m_drawScreen)
		{
			m_font.Begin(rc);
			if (m_drawScreen == AllScreen)
			{
				//1画面の時は大きさそのまま。
				m_font.Draw(m_text.c_str(), m_position, m_color, m_rotation, m_scale, m_pivot);
			}
			else
			{
				//2画面分割の時は縦長に潰れるので横に2倍伸ばす。
				m_font.Draw(m_text.c_str(), m_position, m_color, m_rotation, { m_scale.x * SPLITSCREEN_ASPECT_ADJUSTMENT_VALUE,m_scale.y}, m_pivot);
			}
			m_font.End(rc);
		}
	}
}