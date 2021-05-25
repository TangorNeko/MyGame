#pragma once

namespace prefab
{
	class CEffect2D : public IGameObject
	{
	public:
		CEffect2D();
		~CEffect2D();

		/// <summary>
		/// �������B
		/// </summary>
		/// <remark>
		/// �G�t�F�N�g�Đ��̂��߂̏������s���܂��B
		/// </remark>
		/// <param name="filePath">�t�@�C���p�X</param>
		void Init(const char16_t* filePath);
		/// <summary>
		/// �Đ��J�n
		/// </summary>
		/// <remark>
		/// ���̊֐����Ăяo���ƃG�t�F�N�g�̍Đ����J�n����܂��B
		/// </remark>
		void Play();

		//�Đ����~
		void Stop();

		/*!
		*@brief	���W��ݒ�B
		*/
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		*@brief	��]�N�H�[�^�j�I����ݒ�B
		*/
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// ��]�N�H�[�^�j�I�����擾�B
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}
		/*!
			*@brief	�g�嗦��ݒ�B
			*/
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �g�嗦���擾�B
		/// </summary>
		/// <returns></returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}
		/// <summary>
		/// �G�t�F�N�g���Đ���������B
		/// </summary>
		bool IsPlay() const
		{
			return EffectEngine::GetInstance()->IsPlay2D(m_handle);
		}
		/*!
		 *@brief	�X�V�B
		 */
		void Update();
	private:
		Effekseer::EffectRef m_effect;	//�G�t�F�N�g
		int	m_handle = -1;				//�Đ����̃G�t�F�N�g�̃n���h���B
		Vector3 m_position;				//���W�B
		Quaternion m_rotation;;			//��]�B
		Vector3 m_scale = g_vec3One;	//�g�嗦�B
	};
}
