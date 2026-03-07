# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (Engine)

set(PROJECT_SOURCE_FILES
        source/Engine.h
        source/Engine.cpp
        source/Application.h
        source/Application.cpp
        source/eng.h
        source/input/InputManager.h
        source/input/InputManager.cpp
        source/graphics/ShaderProgram.h
        source/graphics/ShaderProgram.cpp
        source/graphics/GraphicsAPI.h
        source/graphics/GraphicsAPI.cpp
        source/render/Material.h
        source/render/Material.cpp
        source/render/Mesh.cpp
        source/render/Mesh.h
        source/graphics/VertexLayout.h
        source/render/RenderQueue.cpp
        source/render/RenderQueue.h
        source/scene/GameObject.cpp
        source/scene/GameObject.h
        source/scene/Scene.cpp
        source/scene/Scene.h
        source/scene/components/CameraComponent.cpp
        source/scene/components/CameraComponent.h
        source/scene/components/MeshComponent.cpp
        source/scene/components/MeshComponent.h
        source/scene/Component.cpp
        source/scene/Component.h
)

include_directories(source)
add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add GLFW library
add_subdirectory(thirdparty/glfw-3.4 "${CMAKE_CURRENT_BINARY_DIR}/glfw_build")
include_directories(thirdparty/glfw-3.4/include)

# Add Glew library
set(BUILD_UTILS OFF CACHE BOOL "utilities" FORCE)
add_subdirectory(thirdparty/glew/build/cmake "${CMAKE_CURRENT_BINARY_DIR}/glew_build")
include_directories(thirdparty/glew/include)
set_property(TARGET glew_s PROPERTY FOLDER GLEW)
set_property(TARGET glew PROPERTY FOLDER GLEW)

# Add GLM library
add_subdirectory(thirdparty/glm-1.0.1/glm)
include_directories(thirdparty/glm-1.0.1)

# Link all thirdparty libraries
target_link_libraries(${PROJECT_NAME}
        glfw
        glew_s
        glm
)
