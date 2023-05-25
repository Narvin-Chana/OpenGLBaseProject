#include "Test.h"

#include "Camera.h"
#include "imgui/imgui.h"

namespace test
{
    TestMenu::TestMenu(Test*& currentTestPointer, GLFWwindow* w) : Test(w), currentTest(currentTestPointer)
    {
    }

    void TestMenu::OnImGuiRender()
    {
        Test::OnImGuiRender();

        for (auto& test : tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                currentTest = test.second(window);
            }
        }
    }
}
