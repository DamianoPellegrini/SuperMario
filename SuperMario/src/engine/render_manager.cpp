#include "pch.hpp"
#include "render_manager.hpp"

namespace engine {
    void render_manager::init(render_manager_config config) {
        spdlog::info("Initializing render manager...");
        this->_config = config;

        this->createInstance();
        this->setupDebugCallback();
        this->createSurface();
        this->pickPhysicalDevice();
        this->createLogicalDevice();
        this->createSwapChain();
        this->createImageViews();
        this->createGraphicsPipeline();
    }

    void render_manager::shutdown() {
        spdlog::info("Shutting down render manager...");

        for (auto&& imageView : this->_swapChainImageViews) {
            this->_device.destroyImageView(imageView);
        }

        this->_device.destroySwapchainKHR(this->_swapChain);
        this->_device.destroy();
        if (this->_enableDebugMode) {
            this->_instance.destroyDebugUtilsMessengerEXT(this->_debugMessenger, nullptr);
        }

        this->_instance.destroySurfaceKHR(this->_surface, nullptr);
        this->_instance.destroy();
    }

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

    vk::Bool32 VKAPI_CALL render_manager::debugCallback(
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

    bool render_manager::checkValidationLayerSupport() {
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

    void render_manager::setupDebugCallback() {
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
            (PFN_vkDebugUtilsMessengerCallbackEXT)&render_manager::debugCallback,
            nullptr
        };

        this->_debugMessenger = this->_instance.createDebugUtilsMessengerEXT(messInfo);
    }

    void render_manager::createInstance() {
        if (this->_enableDebugMode && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        vk::ApplicationInfo appInfo(
            this->_config.title.c_str(),
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

    // TODO: can be done with macros like layers and device extensions
    std::vector<const char*> render_manager::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (this->_enableDebugMode) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    void render_manager::createSurface() {
        VkSurfaceKHR surface;
        if (glfwCreateWindowSurface(this->_instance, this->_config.window, nullptr, &surface) != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface!");

        this->_surface = vk::SurfaceKHR(surface);
    }

    void render_manager::pickPhysicalDevice() {

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
    int32_t render_manager::rateDeviceSuitability(vk::PhysicalDevice device) {
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

    bool render_manager::isDeviceSuitable(vk::PhysicalDevice device, const vk::PhysicalDeviceProperties* deviceProperties = nullptr, const vk::PhysicalDeviceFeatures* deviceFeatures = nullptr) {
        // If device structs are not provided fetch them using the handle
        auto properties = deviceProperties != nullptr ? *deviceProperties : device.getProperties();
        auto features = deviceFeatures != nullptr ? *deviceFeatures : device.getFeatures();

        renderer::QueueFamilyIndices indices = this->findQueueFamilies(device);
        bool deviceExtSupported = this->checkDeviceExtensionSupport(device);

        // control the swap chain only swap chain extension is supported
        bool swapChainAdequate = false;
        if (deviceExtSupported) {
            auto swapChainSupport = this->querySwapChainSupport(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && deviceExtSupported && swapChainAdequate; // && deviceFeatures.geometryShader;
    }

    renderer::QueueFamilyIndices render_manager::findQueueFamilies(vk::PhysicalDevice device) {
        renderer::QueueFamilyIndices indices;
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

    bool render_manager::checkDeviceExtensionSupport(vk::PhysicalDevice device) {
        std::vector<vk::ExtensionProperties> availableExtensions = device.enumerateDeviceExtensionProperties();

        std::set<std::string> requiredExtensions(this->_deviceExtensions.begin(), this->_deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    void render_manager::createLogicalDevice() {
        renderer::QueueFamilyIndices indices = this->findQueueFamilies(this->_physicalDevice);
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

    renderer::SwapChainSupportDetails render_manager::querySwapChainSupport(vk::PhysicalDevice device) {
        renderer::SwapChainSupportDetails details;

        details.capabilities = device.getSurfaceCapabilitiesKHR(this->_surface);
        details.formats = device.getSurfaceFormatsKHR(this->_surface);
        details.presentModes = device.getSurfacePresentModesKHR(this->_surface);

        return details;
    }

    vk::SurfaceFormatKHR render_manager::chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) {
        if (availableFormats.size() == 1 && availableFormats[0].format == vk::Format::eUndefined) {
            return { vk::Format::eB8G8R8A8Srgb, vk::ColorSpaceKHR::eSrgbNonlinear };
        }

        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == vk::Format::eB8G8R8A8Srgb && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    vk::PresentModeKHR render_manager::chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) {
        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
                return availablePresentMode;
            }
        }

        return vk::PresentModeKHR::eFifo;
    }

    vk::Extent2D render_manager::chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
            return capabilities.currentExtent;

        int width, height;
        glfwGetFramebufferSize(this->_config.window, &width, &height);

        vk::Extent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }

    void render_manager::createSwapChain() {
        auto swapChainSupport = this->querySwapChainSupport(this->_physicalDevice);

        auto surfaceFormat = this->chooseSwapSurfaceFormat(swapChainSupport.formats);
        auto presentMode = this->chooseSwapPresentMode(swapChainSupport.presentModes);
        auto extent = this->chooseSwapExtent(swapChainSupport.capabilities);

        auto imageCount = swapChainSupport.capabilities.minImageCount + 1;

        // if there's a maximum and it's exceeded clamp it back
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        auto indices = this->findQueueFamilies(this->_physicalDevice);
        bool sameQueueFamily = indices.graphicsFamily == indices.presentFamily;
        std::vector<uint32_t> queueFamilyIndices = sameQueueFamily ? std::vector<uint32_t>{} : std::vector<uint32_t>{ indices.graphicsFamily.value(), indices.presentFamily.value() };

        vk::SwapchainCreateInfoKHR swapInfo{
            {},
            this->_surface,
            imageCount,
            surfaceFormat.format,
            surfaceFormat.colorSpace,
            extent,
            1,
            vk::ImageUsageFlagBits::eColorAttachment,
            sameQueueFamily ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent,
            queueFamilyIndices,
            swapChainSupport.capabilities.currentTransform,
            vk::CompositeAlphaFlagBitsKHR::eOpaque,
            presentMode,
            VK_TRUE,
            nullptr
        };

        this->_swapChain = this->_device.createSwapchainKHR(swapInfo);

        this->_swapChainImages = this->_device.getSwapchainImagesKHR(this->_swapChain);
        this->_swapChainImageFormat = surfaceFormat.format;
        this->_swapChainExtent = extent;
    }

    void render_manager::createImageViews() {
        this->_swapChainImageViews.resize(this->_swapChainImages.size());

        for (size_t i = 0; i < this->_swapChainImages.size(); i++) {
            vk::ImageViewCreateInfo viewInfo{
                {},
                this->_swapChainImages[i],
                vk::ImageViewType::e2D,
                this->_swapChainImageFormat,
                {
                    vk::ComponentSwizzle::eR,
                    vk::ComponentSwizzle::eG,
                    vk::ComponentSwizzle::eB,
                    vk::ComponentSwizzle::eA
                },
                {
                    vk::ImageAspectFlagBits::eColor,
                    0,
                    1,
                    0,
                    1
                }
            };

            this->_swapChainImageViews[i] = this->_device.createImageView(viewInfo);
        }
    }

    void render_manager::createGraphicsPipeline() {
        // TODO: Load Shaders
    }
} // namespace engine
