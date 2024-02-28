#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
namespace LM {
	class Sprite
	{
	protected:
		float m_RotationRad;
		const Shader* m_Shader;
		const Camera* m_Camera;
		bool m_Enable;
		// 父结点
		const Sprite* m_Parent;
		// 子结点
		std::vector<Sprite*> m_Children;
		// Meshes
		std::vector<Mesh*> m_Meshes;
		Sprite(Shader* shader = nullptr,Camera* camera = nullptr, Sprite* parent = nullptr, float rotationRad = 0.0f);
		
	public:
		virtual ~Sprite();

		// 设置uniform变量
		virtual void SetUniform() = 0;
		
		virtual void SetCamera(Camera* camera);
		virtual const Camera* GetCamera() const;

		virtual void Draw();

		virtual void SetShader(Shader* shader);
		virtual const Shader* GetShader() const;

		virtual void AddMeshes(Mesh* mesh);

		virtual void AddChild(Sprite* sprite);
		// ------- 旋转角度 ------------
		// 设置旋转角度
		void SetRotationRad(float rad);
		// 获得旋转角度
		float GetRotationRad() const;
		// 旋转角度增加rad
		void Rotate(float rad);
	};
}
