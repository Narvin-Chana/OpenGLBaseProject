#pragma once
#include "Test.h"

namespace test
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor(GLFWwindow* w);
        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float clearColor[4];
    };
}
