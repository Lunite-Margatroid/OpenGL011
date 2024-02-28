#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
namespace LM {
	class Sprite
	{
	protected:
		const Shader* m_Shader;
		const Camera* m_Camera;
		bool m_Enable;
		// Meshes
		std::vector<Mesh*> m_Meshes;
		Sprite(Shader* shader = nullptr,Camera* camera = nullptr);
		
	public:
		virtual ~Sprite();

		// ����uniform����
		virtual void SetUniform() = 0;
		
		virtual void SetCamera(Camera* camera);
		virtual const Camera* GetCamera() const;

		virtual void Draw(glm::mat4 objMoudleTrans);

		virtual void SetShader(Shader* shader);
		virtual const Shader* GetShader() const;

		virtual void AddMeshes(Mesh* mesh);
		// ------- ��ת�Ƕ� ------------
		// ������ת�Ƕ�
		void SetRotationRad(float rad);
		// �����ת�Ƕ�
		float GetRotationRad() const;
		// ��ת�Ƕ�����rad
		void Rotate(float rad);
	};
}
