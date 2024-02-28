#pragma once

namespace LM
{
	class Object
	{
	protected:

		// ---- �ṹ ------
		// �����
		const Object* m_Parent;
		// �ֽ��
		std::vector<Object*> m_Children;
		
		// ----- bool ----
		bool m_Enable;			// �Ƿ����
		bool m_Render;			// �Ƿ���Ⱦ

		//---- λ�� ----
		float m_RotationRad;	// ��ת��
		// ��ת��
		// λ��
		// ����

		//----- �˶����� ----
		bool m_Movable;			// �Ƿ���ƶ�
		bool m_Rotatable;		// �Ƿ����ת
		bool m_Deformable;		// �Ƿ������

		// --------- ���������� ---------


	public:
		// --------- ���������� ---------


		// --------- �ṹ -----------
		void SetParent(Object* object);
		const Object* GetParent() const;

		void AddChild(Object* object);

		// ----- bool ----
		void Enable();
		void Disable();
		bool IsEnable() const;

		void Renderable();
		void DisRenderable();
		bool IsRenderable() const;

		// ---- λ�� ----
		// -��ת��-

		float GetRotation();			// �����ת��
		void Rotate(float rad);			// ��תrad
		float SetRotation(float rad);	// ������ת��Ϊrad

		// -��ת��- Object3Dһ��Ҫ������Щ

		virtual glm::vec3 GetRotationAxis() const;
		virtual void SetRotationAxis(const glm::vec3&);

		// -λ��-

		/* ��������ʵ�� */

		// -����-

		/* ��������ʵ�� */


		//----- �˶����� ---------
	};
}

