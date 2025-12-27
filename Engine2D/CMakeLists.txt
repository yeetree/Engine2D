# Engine2D

# Engine2D sources
set(E2D_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/src/gl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Core/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Core/Timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Core/FileSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Core/AssetManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Core/Platform/SDL3/SDL3Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Core/Platform/SDL3/OpenGL/SDL3_OpenGLWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Renderer/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Renderer/Renderer2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Renderer/Platform/OpenGL/OpenGLTexture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Renderer/Platform/OpenGL/OpenGLMesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Renderer/Platform/OpenGL/OpenGLShader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Renderer/Platform/OpenGL/OpenGLRendererAPI.cpp
)

# Engine2D includes
set(E2D_PUBLIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}../vendor/glm
)

set(E2D_PRIVATE_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/stb
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/SDL/include
)

if(E2D_ENABLE_IMGUI)
    target_compile_definitions(Engine2D PUBLIC E2D_ENABLE_IMGUI)

    list(APPEND E2D_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/misc/cpp/imgui_stdlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/backends/imgui_impl_sdl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/backends/imgui_impl_opengl3.cpp
    )

    list(APPEND E2D_PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui/backends  
    )
endif()

# Build and link Engine2D
add_library(Engine2D STATIC ${E2D_SOURCES})
add_library(Engine2D::Engine2D ALIAS Engine2D)
target_link_libraries(Engine2D PRIVATE OpenGL::GL SDL3::SDL3)
target_include_directories(Engine2D PUBLIC ${E2D_PUBLIC_INCLUDES})
target_include_directories(Engine2D PRIVATE ${E2D_PRIVATE_INCLUDES})

if(E2D_ENABLE_IMGUI)
    target_compile_definitions(Engine2D PUBLIC E2D_ENABLE_IMGUI)
endif()