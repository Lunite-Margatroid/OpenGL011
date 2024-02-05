#pragma once
#include "Test.h"
#include "imgui/imgui.h"
namespace test
{
	class TestClearColor :public Test
	{
	private:
		float m_color[4];
	public:
		TestClearColor();
		~TestClearColor();

		void OnRender() override;
		void OnRenderImgui() override;
	};
}