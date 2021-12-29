#include "pch.hpp"
#include "vulkan_manager.hpp"

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

namespace engine {
    vulkan_manager::vulkan_manager(const std::string& application_name)
        : _application_name(application_name) {
        this->createInstance();
        this->setupDebugCallback();
        this->pickPhysicalDevice();
    }

    vulkan_manager::~vulkan_manager() {
        if (this->_enableDebugMode) {
            DestroyDebugUtilsMessengerEXT(this->_instance, this->_debugMessenger, nullptr);
        }

        vkDestroyInstance(this->_instance, nullptr);
    }

    void vulkan_manager::createInstance() {
        if (this->_enableDebugMode && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = this->_application_name.c_str(),
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "No Engine",
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_2
        };

        const auto& extensions = this->getRequiredExtensions();

        VkInstanceCreateInfo createInfo{
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &appInfo,
            .enabledLayerCount = this->_enableDebugMode ? (uint32_t)this->_validationLayers.size() : 0,
            .ppEnabledLayerNames = this->_enableDebugMode ? this->_validationLayers.data() : nullptr,
            .enabledExtensionCount = (uint32_t)extensions.size(),
            .ppEnabledExtensionNames = extensions.data(),
        };

        if (vkCreateInstance(&createInfo, nullptr, &this->_instance) != VkResult::VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan instance!");

        uint32_t extensionCount;

        // Get extension count
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        this->_extensions = std::vector<VkExtensionProperties>{ extensionCount };

        // Get extension information
        if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, this->_extensions.data()) != VkResult::VK_SUCCESS)
            throw std::runtime_error("Failed to enumerate Vulkan instance extensions!");
    }

    bool vulkan_manager::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const auto& layerName : this->_validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    std::vector<const char*> vulkan_manager::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (this->_enableDebugMode) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void vulkan_manager::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(this->_instance, &deviceCount, nullptr);
        if (deviceCount == 0)
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(this->_instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (this->isDeviceSuitable(device)) {
                this->_physicalDevice = device;
                break;
            }
        }

        if (this->_physicalDevice == VK_NULL_HANDLE)
            throw std::runtime_error("Failed to find a suitable GPU!");


    }

    bool vulkan_manager::isDeviceSuitable(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        const char* deviceType = nullptr;
        switch (deviceProperties.deviceType) {
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            deviceType = "Integrated GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            deviceType = "Discrete GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            deviceType = "Virtual GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            deviceType = "CPU";
            break;
        default:
            deviceType = "Unknown";
            break;
        }

        spdlog::info(
            "[Physical Device] [{}] {} (driver: {}) (api: {}.{}.{})",
            deviceType,
            deviceProperties.deviceName,
            deviceProperties.driverVersion,
            VK_VERSION_MAJOR(deviceProperties.apiVersion),
            VK_VERSION_MINOR(deviceProperties.apiVersion),
            VK_VERSION_PATCH(deviceProperties.apiVersion)
        );


        return true;

        // Implement GPU scoring
        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
            && deviceFeatures.geometryShader;
    }

    void vulkan_manager::setupDebugCallback() {
        if (!this->_enableDebugMode) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = vulkan_manager::debugCallback,
            .pUserData = nullptr,
        };

        if (CreateDebugUtilsMessengerEXT(this->_instance, &createInfo, nullptr, &this->_debugMessenger) != VkResult::VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug callback!");
        }
    }

    VkBool32 VKAPI_CALL vulkan_manager::debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {
        const char* type = nullptr;

        switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            type = "GENERAL";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            type = "VALIDATION";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
            type = "PERFORMANCE";
            break;
            default:
            type = "UNKNOWN";
            break;
        }

        switch (messageSeverity) {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                spdlog::trace("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                spdlog::info("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                spdlog::warn("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                spdlog::error("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
                break;
            default:
                spdlog::critical("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
        }

        return VK_FALSE; // continue propagating
    }

    void vulkan_manager::run() {}

} // namespace engine
