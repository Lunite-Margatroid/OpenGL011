#pragma once
#include "Test.h"
#include "Camera_K.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "PointLight.h"
namespace test
{
    class TestBlinn :
        public Test
    {
    private:
        LM::Shader m_shader;
        LM::Shader m_shaderPhong;
        LM::Shader m_shaderBlinn;
        LM::Texture m_texture;
        LM::VertexBuffer m_vbo;
        LM::ElementBuffer m_ebo;
        LM::VertexArray m_vao;
        LM::PointLight m_pointLight;
        bool m_blinn;
        float m_shininess;
        LM::Shader* m_currentShader;
    public:
        TestBlinn();
        ~TestBlinn();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnRenderImgui() override;
    };

}