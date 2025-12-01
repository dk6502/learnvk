#include "VkBootstrap.h"
#include <GLFW/glfw3.h>
#include <print>
#include <stdexcept>
#include <string>
#include <vulkan/vulkan_core.h>
#include <vulkan/vulkan_raii.hpp>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  GLFWwindow *window = nullptr;
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  void initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "woah", nullptr, nullptr);
  }
  void initVulkan() {
    vkb::InstanceBuilder builder;
    auto inst_ret = builder.set_app_name("triangle!?!")
                        .request_validation_layers()
                        .use_default_debug_messenger()
                        .build();
    if (!inst_ret)
      throw std::runtime_error("Could not build a vulkan instance");
    vkb::Instance vkb_inst = inst_ret.value();
    VkResult glfw_result = glfwCreateWindowSurface(vkb_inst, window, nullptr, &surface);
    if (glfw_result != VK_SUCCESS) throw std::runtime_error("Failed to initialize vulkan surface");
  }

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    glfwDestroyWindow(window);

    glfwTerminate();
  }

  void createInstance() {}
};

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::println(stderr,"{}", e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
