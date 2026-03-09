# Engine CMakeLists.txt
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("GameEngine")
set(PROJECT_SOURCE_FILES
        source/main.cpp
        source/Game.h
        source/Game.cpp
        source/TestObject.cpp
        source/TestObject.h
        source/Player.h
        source/Player.cpp
        source/Bullet.h
        source/Bullet.cpp
        source/JumpPlatform.h
        source/JumpPlatform.cpp
        source/Bullet.cpp
        source/Bullet.h
        source/JumpPlatform.cpp
        source/JumpPlatform.h
        source/Player.cpp
        source/Player.h
)

include_directories(engine/thirdparty/glew/include)
include_directories(engine/thirdparty/glm-1.0.1)

# Add the application
include_directories(engine/source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

include_directories(engine/thirdparty/stb_image)
include_directories(engine/thirdparty/json)

# Add engine library
add_compile_definitions(GLEW_NO_GLU)
add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")
target_link_libraries(${PROJECT_NAME}
        Engine
)