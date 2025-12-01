cmake_minimum_required(VERSION 3.31)
project(learnvk)

include(FetchContent)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)

find_package(Vulkan)
FetchContent_Declare(
    vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG        v1.4.334 #suggest using a tag so the library doesn't update whenever new commits are pushed to a branch
)
FetchContent_MakeAvailable(vk_bootstrap)

FetchContent_Declare(
    glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

add_executable(triangle
  triangle/main.cc)
target_link_libraries(triangle
  vk-bootstrap::vk-bootstrap
  glfw)
