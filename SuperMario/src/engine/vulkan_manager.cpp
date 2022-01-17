#include "pch.hpp"
#include "vulkan_manager.hpp"

namespace engine {

    void printPhysicalDeviceInfo(vk::PhysicalDevice device) {
        auto deviceProperties = device.getProperties();
        auto deviceFeatures = device.getFeatures();

        const char* deviceType = nullptr;
        switch (deviceProperties.deviceType) {
        case vk::PhysicalDeviceType::eIntegratedGpu:
            deviceType = "Integrated GPU";
            break;
        case vk::PhysicalDeviceType::eDiscreteGpu:
            deviceType = "Discrete GPU";
            break;
        case vk::PhysicalDeviceType::eVirtualGpu:
            deviceType = "Virtual GPU";
            break;
        case vk::PhysicalDeviceType::eCpu:
            deviceType = "CPU";
            break;
        default:
            deviceType = "Unknown";
            break;
        }

        spdlog::info(
            "[Physical Device] [{}] {} (driver: {}.{}.{}) (api: {}.{}.{})",
            deviceType,
            deviceProperties.deviceName,
            VK_VERSION_MAJOR(deviceProperties.driverVersion),
            VK_VERSION_MINOR(deviceProperties.driverVersion),
            VK_VERSION_PATCH(deviceProperties.driverVersion),
            VK_VERSION_MAJOR(deviceProperties.apiVersion),
            VK_VERSION_MINOR(deviceProperties.apiVersion),
            VK_VERSION_PATCH(deviceProperties.apiVersion)
        );
    }

    vulkan_manager::vulkan_manager(const std::string& application_name, std::shared_ptr<glfw_manager> glfw_manager)
        : _application_name(application_name), _glfw_manager(glfw_manager) {
        this->createInstance();
        this->setupDebugCallback();
        this->createSurface();
        this->pickPhysicalDevice();
        this->createLogicalDevice();
    }

    vulkan_manager::~vulkan_manager() {
        this->_device.destroy();
        if (this->_enableDebugMode) {
            this->_instance.destroyDebugUtilsMessengerEXT(this->_debugMessenger, nullptr);
        }

        this->_instance.destroySurfaceKHR(this->_surface, nullptr);
        this->_instance.destroy();
    }

    void vulkan_manager::createInstance() {
        if (this->_enableDebugMode && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        vk::ApplicationInfo appInfo(
            this->_application_name.c_str(),
            VK_MAKE_VERSION(1, 0, 0),
            "No Engine",
            VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_2);

        const auto& extensions = this->getRequiredExtensions();

        vk::InstanceCreateInfo instInfo(
            {},
            &appInfo,
            this->_validationLayers,
            extensions
        );

        this->_instance = vk::createInstance(instInfo);
        this->_extensions = vk::enumerateInstanceExtensionProperties();
    }

    bool vulkan_manager::checkValidationLayerSupport() {
        std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();

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

    void vulkan_manager::setupDebugCallback() {
        if (!this->_enableDebugMode) return;

        vk::DebugUtilsMessengerCreateInfoEXT messInfo{
            {},
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo,
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
            vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
            vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            (PFN_vkDebugUtilsMessengerCallbackEXT)&vulkan_manager::debugCallback,
            nullptr
        };

        this->_debugMessenger = this->_instance.createDebugUtilsMessengerEXT(messInfo);
    }

    vk::Bool32 VKAPI_CALL vulkan_manager::debugCallback(
        vk::DebugUtilsMessageSeverityFlagsEXT messageSeverity,
        vk::DebugUtilsMessageTypeFlagsEXT messageType,
        const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {
        const char* type = nullptr;

        if (messageType & vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral) {
            type = "GENERAL";
        }
        else if (messageType & vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation) {
            type = "VALIDATION";
        }
        else if (messageType & vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance) {
            type = "PERFORMANCE";
        }
        else {
            type = "UNKNOWN";
        }

        if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose) {
            spdlog::trace("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
        }
        else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo) {
            spdlog::info("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
        }
        else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
            spdlog::warn("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
        }
        else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eError) {
            spdlog::error("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
        }
        else {
            spdlog::critical("[VK_DEBUG] [{}] {}", type, pCallbackData->pMessage);
        }

        return VK_FALSE; // continue propagation
    }

    void vulkan_manager::createSurface() {
        VkSurfaceKHR surface;
        if (glfwCreateWindowSurface(this->_instance, this->_glfw_manager->get_window(), nullptr, &surface) != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface!");

        this->_surface = vk::SurfaceKHR(surface);
    }

    void vulkan_manager::pickPhysicalDevice() {

        auto devices = this->_instance.enumeratePhysicalDevices();

        std::multimap<int32_t, vk::PhysicalDevice> candidates;

        for (const auto& device : devices) {
            int32_t score = this->rateDeviceSuitability(device);
            candidates.insert(std::make_pair(score, device));
        }

        if (candidates.rbegin()->first > -1)
            this->_physicalDevice = candidates.rbegin()->second;
        else
            throw std::runtime_error("failed to find a suitable GPU!");

        printPhysicalDeviceInfo(this->_physicalDevice);
    }

    /// <summary>
    /// Returns a score for the device based on how well it matches the requested properties.
    /// </summary>
    /// <param name="device">The device to rate.</param>
    /// <returns>A positive score, negative means invalid</returns>
    int32_t vulkan_manager::rateDeviceSuitability(vk::PhysicalDevice device) {
        auto deviceProperties = device.getProperties();
        auto deviceFeatures = device.getFeatures();


        if (!this->isDeviceSuitable(device, &deviceProperties, &deviceFeatures)) return -1;

        int32_t score = 0;
        if (deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
            score += 10000;
        if (deviceProperties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu)
            score += 1000;

        return score;
    }

    bool vulkan_manager::isDeviceSuitable(vk::PhysicalDevice device, const vk::PhysicalDeviceProperties* deviceProperties = nullptr, const vk::PhysicalDeviceFeatures* deviceFeatures = nullptr) {
        // If device structs are not provided fetch them using the handle
        auto properties = deviceProperties != nullptr ? *deviceProperties : device.getProperties();
        auto features = deviceFeatures != nullptr ? *deviceFeatures : device.getFeatures();

        QueueFamilyIndices indices = this->findQueueFamilies(device);

        return indices.isComplete() && this->checkDeviceExtensionSupport(device); // && deviceFeatures.geometryShader;
    }

    QueueFamilyIndices vulkan_manager::findQueueFamilies(vk::PhysicalDevice device) {
        QueueFamilyIndices indices;
        auto queueFamilies = device.getQueueFamilyProperties();

        uint32_t i = 0;
        for (const auto& queueFamily : queueFamilies) {

            if (queueFamily.queueCount <= 0) continue;

            if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
            }

            if (queueFamily.queueFlags & vk::QueueFlagBits::eCompute) {
                indices.computeFamily = i;
            }

            if (queueFamily.queueFlags & vk::QueueFlagBits::eTransfer) {
                indices.transferFamily = i;
            }

            if (device.getSurfaceSupportKHR(i, this->_surface)) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    bool vulkan_manager::checkDeviceExtensionSupport(vk::PhysicalDevice device) {
        std::vector<vk::ExtensionProperties> availableExtensions = device.enumerateDeviceExtensionProperties();

        std::set<std::string> requiredExtensions(this->_deviceExtensions.begin(), this->_deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    void vulkan_manager::createLogicalDevice() {
        QueueFamilyIndices indices = this->findQueueFamilies(this->_physicalDevice);
        std::unordered_set<std::uint32_t> uniqueIndices{
            indices.graphicsFamily.value(),
            indices.presentFamily.value()
        };
        float queuePriority = 1.0f;
        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;

        for (const auto& uniqueIndex : uniqueIndices) {
            vk::DeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.queueFamilyIndex = uniqueIndex;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        // Used to specify which features are used effectively
        vk::PhysicalDeviceFeatures deviceFeatures{};
        
        vk::DeviceCreateInfo deviceInfo{
            {},
            queueCreateInfos,
            this->_validationLayers,
            this->_deviceExtensions,
            &deviceFeatures
        };

        this->_device = this->_physicalDevice.createDevice(deviceInfo);
        this->_graphicsQueue = this->_device.getQueue(indices.graphicsFamily.value(), 0);
        this->_presentQueue = this->_device.getQueue(indices.presentFamily.value(), 0);
    }

    void vulkan_manager::run() {}

} // namespace engine
