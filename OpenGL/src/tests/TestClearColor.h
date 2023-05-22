#pragma once
#include "Test.h"

namespace test
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor() override;

        void OnUpdate(float deltaTime, GLFWwindow* window) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        float clearColor[4];
    };
    
}
