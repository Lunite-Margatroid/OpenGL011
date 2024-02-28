#include "pch.h"
#include "Sprite.h"

namespace LM
{
	Sprite::Sprite(Shader* shader, Camera* camera, Sprite* parent, float rotationRad)
		:m_Shader(shader), m_Parent(parent), m_RotationRad(rotationRad)
	{
	}
	Sprite::~Sprite()
	{
	}
}