#include "Engine.h"
#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace eng
{
    void keyCallback(GLFWwindow* window, int key, int, int action, int)
    {
        auto& inputManager = eng::Engine::GetInstance().GetInputManager();
        if (action == GLFW_PRESS)
        {
            inputManager.SetKeyPressed(key, true);
        }
        else if (action == GLFW_RELEASE)
        {
            inputManager.SetKeyPressed(key, false);
        }
    }
     Engine& Engine::GetInstance()
     {
         static Engine instance;
         return instance;
     }
    bool Engine::Init(int width, int height)
    {
        if(!m_application)
        {
            return false;
        }

        if (!glfwInit())
        {
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(width, height, "WorldEngine", nullptr, nullptr); // Create Window

        if (m_window == nullptr) // Check if Window was successfully created
        {
            std::cout << "Error creating window" << std::endl;
            glfwTerminate();  //Clean GLFW Library
            return false;
        }

        glfwSetKeyCallback(m_window, keyCallback);

        glfwMakeContextCurrent(m_window);

        if (glewInit() != GLEW_OK)
        {
            glfwTerminate();
            return false;
        }

        return m_application->Init();
    }

    void Engine::Run()
    {
      if(!m_application)
      {
          return;
      }

      // Initialize time tracking
      m_lastTimePoint = std::chrono::steady_clock::now();

      while (!glfwWindowShouldClose(m_window) && !m_application->NeedsToBeClosed())
      {
          glfwPollEvents();
        auto now = std::chrono::steady_clock ::now();
        float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
        m_lastTimePoint = now;

        m_application->Update(deltaTime);

          glfwSwapBuffers(m_window);
      }
    }

    void Engine::Destroy()
    {
      if(m_application)
      {
          m_application->Destroy();
          m_application.reset();
          glfwTerminate();
          m_window = nullptr;
      }
    }

    void Engine::SetApplication(Application* app)
    {
         m_application.reset(app);
    }

    Application* Engine::GetApplication()
    {
        return m_application.get();
    }

    InputManager& Engine::GetInputManager()
    {
        return m_inputManager;
    }
}