#pragma once
#include <functional>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"

namespace test
{
    class Test
    {
    protected:
        GLFWwindow* window;

    public:
        Test(GLFWwindow* window)
        {
            this->window = window;
        }

        virtual ~Test() = default;

        virtual void OnUpdate(float deltaTime)
        {
        }

        virtual void OnRender()
        {
        }

        virtual void OnImGuiRender()
        {
        }
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& currentTestPointer, GLFWwindow* w);

        void OnImGuiRender() override;

        template <typename T>
        void RegisterTest(const std::string& name)
        {
            std::cout << "Registering test " << name << std::endl;
            tests.push_back(std::make_pair(name, [this](GLFWwindow* window) { return new T(window); }));
        }
        
    private:
        Test*& currentTest;
        std::vector<std::pair<std::string, std::function<Test*(GLFWwindow*)>>> tests;
    };
}
