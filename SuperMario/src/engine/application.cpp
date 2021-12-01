#include "pch.hpp"
#include "application.hpp"

namespace engine {

    application::application(std::string title, uint32_t width, uint32_t height)
        : _title(title), _width(width), _height(height) {
        initGLFW();
        initVulkan();
    }

    application::~application() {
        cleanupVulkan();
        cleanupGLFW();
    }

    void application::run() {
        mainLoop();
    }

    void application::mainLoop() {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
        }
    }

    void application::initGLFW() {
        if (glfwInit() != GLFW_TRUE)
            throw std::runtime_error("Failed to initialize GLFW!");
        // Disable default OpenGL Context creation
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FOCUSED, DEBUG ? GLFW_FALSE : GLFW_TRUE);
        // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        this->_window = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), nullptr, nullptr);
    }

    void application::cleanupGLFW() {
        glfwDestroyWindow(this->_window);
        glfwTerminate();
    }

    void application::initVulkan() {
        VkApplicationInfo appInfo{
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = this->_title.c_str(),
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "No Engine",
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_2
        };

        uint32_t extensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

        VkInstanceCreateInfo createInfo{
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &appInfo,
            .enabledExtensionCount = extensionCount,
            .ppEnabledExtensionNames = glfwExtensions,
        };

        if (vkCreateInstance(&createInfo, nullptr, &this->_instance) != VkResult::VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan instance!");

        // Get extension count
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        this->_extensions = std::vector<VkExtensionProperties>{ extensionCount };

        // Get extension information
        if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, this->_extensions.data()) != VkResult::VK_SUCCESS)
            throw std::runtime_error("Failed to enumerate Vulkan instance extensions!");
    }

    void application::cleanupVulkan() {
        vkDestroyInstance(this->_instance, nullptr);
    }

} // namespace engine
