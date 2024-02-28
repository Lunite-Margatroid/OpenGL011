#pragma once

namespace LM
{
	class Object
	{
	protected:

		// ---- 结构 ------
		// 父结点
		const Object* m_Parent;
		// 字结点
		std::vector<Object*> m_Children;
		
		// ----- bool ----
		bool m_Enable;			// 是否可用
		bool m_Render;			// 是否渲染

		//---- 位姿 ----
		float m_RotationRad;	// 旋转角
		// 旋转轴
		// 位置
		// 缩放

		//----- 运动能力 ----
		bool m_Movable;			// 是否可移动
		bool m_Rotatable;		// 是否可旋转
		bool m_Deformable;		// 是否可缩放

		// --------- 构造与析构 ---------


	public:
		// --------- 构造与析构 ---------


		// --------- 结构 -----------
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

		// ---- 位姿 ----
		// -旋转角-

		float GetRotation();			// 获得旋转角
		void Rotate(float rad);			// 旋转rad
		float SetRotation(float rad);	// 设置旋转角为rad

		// -旋转轴- Object3D一定要重载这些

		virtual glm::vec3 GetRotationAxis() const;
		virtual void SetRotationAxis(const glm::vec3&);

		// -位置-

		/* 在子类中实现 */

		// -缩放-

		/* 在子类中实现 */


		//----- 运动能力 ---------
	};
}

