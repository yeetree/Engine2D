# Engine2D
cmake_minimum_required(VERSION 4.0)
project(Engine2D_Workspace VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGL
find_package(OpenGL REQUIRED)

# SDL & GLM
add_subdirectory(vendor/glm)
set(SDL_TEST_LIBRARY OFF CACHE INTERNAL "")
set(SDL_TESTS OFF CACHE INTERNAL "")
set(SDL_DISABLE_INSTALL ON CACHE INTERNAL "")
add_subdirectory(vendor/SDL)

option(E2D_WITH_IMGUI "Enable ImGui support in Engine2D" ON)
if(E2D_WITH_IMGUI)
    add_subdirectory(vendor/imgui)
    target_compile_definitions(Engine2D PUBLIC E2D_ENABLE_IMGUI)
    target_link_libraries(Engine2D PRIVATE imgui::imgui)
endif()

# Engine2D library
add_subdirectory(Engine2D)

option(E2D_BUILD_TEST_APP "Build the test app" ON)

if(E2D_BUILD_TEST_APP)
    add_subdirectory(TestApp)
endif()