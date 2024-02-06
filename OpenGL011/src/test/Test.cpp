#include "pch.h"
#include "Test.h"

namespace test
{
	TestMenu::TestMenu(Test*& currentTest) :m_currentTest(currentTest)
	{

	}
	TestMenu::~TestMenu()
	{
	}
	void TestMenu::OnRenderImgui()
	{
		for (auto& testPair : m_testList)
		{
			if (ImGui::Button(testPair.first.c_str()))
				m_currentTest = testPair.second();
		}
	}
}