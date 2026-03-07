#include "scene/components/PlayerControllerComponent.h"
#include "input/InputManager.h"
#include "Engine.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec4.hpp>

namespace eng
{
    void PlayerControllerComponent::Update(float deltaTime)
    {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        auto eulerRotation = m_owner->GetRotation();
        
        // Convert Euler angles to quaternion for manipulation
        glm::quat rotation = glm::quat(eulerRotation);

        if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            const auto& oldPos = inputManager.GetMousePositionOld();
            const auto& currentPos = inputManager.GetMousePositionCurrent();

            float deltaX = currentPos.x - oldPos.x;
            float deltaY = currentPos.y - oldPos.y;

            // rot around Y axis
            float yAngle = -deltaX * m_sensitivity * deltaTime;
            glm::quat yRot = glm::angleAxis(yAngle, glm::vec3(0.0f, 1.0f, 0.0f));

            // rot around X axis
            float xAngle = -deltaY * m_sensitivity * deltaTime;
            glm::mat4 rotMat = glm::mat4_cast(rotation);
            glm::vec3 right = glm::normalize(glm::vec3(rotMat[0]));
            glm::quat xRot = glm::angleAxis(xAngle, right);

            glm::quat deltaRot = yRot * xRot;
            rotation = glm::normalize(deltaRot * rotation);

            // Convert quaternion back to Euler angles for storage
            // Using standard conversion: Euler = (yaw, pitch, roll) from quat
            glm::vec3 angles = glm::eulerAngles(rotation);
            m_owner->SetRotation(angles);
        }

        // Convert quaternion to matrix for direction vectors
        glm::mat4 rotMat = glm::mat4_cast(rotation);
        glm::vec3 front = -glm::vec3(rotMat[2]);
        glm::vec3 right = glm::vec3(rotMat[0]);

        auto position = m_owner->GetPosition();

        // Left/Right movement
        if (inputManager.IsKeyPressed(GLFW_KEY_A))
        {
            position -= right * m_moveSpeed * deltaTime;
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_D))
        {
            position += right * m_moveSpeed * deltaTime;
        }
        // Vertical movement
        if (inputManager.IsKeyPressed(GLFW_KEY_W))
        {
            position += front * m_moveSpeed * deltaTime;
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_S))
        {
            position -= front * m_moveSpeed * deltaTime;
        }
        m_owner->SetPosition(position);
    }
}