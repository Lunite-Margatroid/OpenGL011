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
		bool m_Enabled;

		// ------------位姿---------------
		// -平移
								// 偏移
								
		// -旋转
		float m_RotationRad;	// 转角 弧度制
								// 转轴

		// -缩放
								//缩放
		


		// Meshes
		std::vector<Mesh*> m_Meshes;
		Sprite(Shader* shader = nullptr,Camera* camera = nullptr, float rotationRad = 0.0f);
		
	public:
		virtual ~Sprite();

		// 设置uniform变量
		virtual void SetUniform() = 0;
		
		virtual void SetCamera(Camera* camera);
		virtual const Camera* GetCamera() const;

		// 3D render
		virtual void Draw(const glm::mat4& objMoudleTrans = glm::mat4(1.0f));
		// 2D render
		virtual void Draw(const glm::vec2& position = glm::vec2(1.0f, 1.0f), float rotationRad = 0.0f, const glm::vec2& scale = glm::vec2(1.0f, 1.0f));

		virtual void SetShader(Shader* shader);
		virtual const Shader* GetShader() const;

		virtual void AddMeshes(Mesh* mesh);
		// ---------- 平移 ----------
		virtual void SetPosition(const glm::vec3& position);
		virtual void SetPosition(const glm::vec2& offset);
		virtual void Move(const glm::vec3& position); 
		virtual void Move(const glm::vec2& position);
		virtual const glm::vec3& GetPosition() const;
		virtual const glm::vec3& GetPosition3v() const;
		virtual const glm::vec2& GetPosition2v() const;


		// ------- 旋转 ------------
		// 设置旋转角度
		void SetRotationRad(float rad);
		// 获得旋转角度
		float GetRotationRad() const;
		// 旋转角度增加rad
		void Rotate(float rad);
		// 旋转轴
		virtual const glm::vec3& GetRotationAxis() const;
		virtual void SetRotationAxis(const glm::vec3& rotationAxis); // 2D这个函数不管用
		// --------- 缩放 ----------
		virtual void SetScale(const glm::vec3& scale);
		virtual void SetScale(const glm::vec2& scale);
		virtual const glm::vec3& GetScale3v() const;
		virtual const glm::vec2& GetScale2v() const;
		virtual void Scale(const glm::vec3& scale);
		virtual void Scale(const glm::vec2& scale);
		

		//----------可用-------------
		bool IsEnabled() const;
		void Enable();
		void Disable();
	};
}
