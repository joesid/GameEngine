#include "render/RenderQueue.h"
#include "render/Mesh.h"
#include "render/Material.h"
#include "graphics/GraphicsAPI.h"


namespace eng
{
    void RenderQueue::Submit(const RenderCommand& command)
    {
        m_commands.push_back(command);
    }

    void RenderQueue::Draw(GraphicsAPI& graphicsAPI)
    {
        for (auto& command : m_commands)
        {
            // Set model matrix on material so Material::Bind uploads it to shader
            if (command.material)
            {
                command.material->SetParam("uModel", command.modelMatrix);
                graphicsAPI.BindMaterial(command.material);
            }

            graphicsAPI.BindMesh(command.mesh);
            graphicsAPI.DrawMesh(command.mesh);
        }

        m_commands.clear();
    }
}