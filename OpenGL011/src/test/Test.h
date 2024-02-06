#pragma once
#include "imgui/imgui.h"
#include <functional>
namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnRenderImgui() {}
	};

	class TestMenu :public Test
	{
	private:
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_testList;
		Test*& m_currentTest;
	public:
		TestMenu(Test*& currentTest);
		~TestMenu();
		template<typename T>
		void RegisterTest(std::string&&);
		void OnRenderImgui() override;
	};

	template<typename T>
	inline void TestMenu::RegisterTest(std::string&& testLabel)
	{
		m_testList.push_back(
			std::make_pair
			(
				testLabel,
				[]() {return new T(); }
			)
		);
	}
}