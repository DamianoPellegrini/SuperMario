#ifndef _VULKAN_MANAGER_HPP_
#define _VULKAN_MANAGER_HPP_

#include "old_manager.hpp"
#include "queue_family_indices.hpp"
#include "swap_chain_support_details.hpp"
#include "glfw_manager.hpp"

namespace engine {
    class vulkan_manager : public old_manager {
    private:
        std::string _application_name;
        std::shared_ptr<glfw_manager> _glfw_manager;

        vk::Instance _instance;

        const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        const std::vector<const char*> _deviceExtensions = {
            #ifdef MACOS
            VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
            #endif
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        std::vector<vk::ExtensionProperties> _extensions;

        vk::DebugUtilsMessengerEXT _debugMessenger;

        vk::SurfaceKHR _surface;

        vk::PhysicalDevice _physicalDevice;

        vk::Device _device;

        vk::Queue _graphicsQueue;
        vk::Queue _presentQueue;

        vk::SwapchainKHR _swapChain;
        std::vector<vk::Image> _swapChainImages;
        vk::Format _swapChainImageFormat;
        vk::Extent2D _swapChainExtent;
        std::vector<vk::ImageView> _swapChainImageViews;

#ifdef NDEBUG
        const bool _enableDebugMode = false;
#else
        const bool _enableDebugMode = true;
#endif

    public:
        vulkan_manager(const std::string& application_name, std::shared_ptr<glfw_manager> glfw_manager);
        virtual ~vulkan_manager() override;
        virtual void run() override;
    private:
        // Debugging and validation
        bool checkValidationLayerSupport();
        void setupDebugCallback();

        std::vector<const char*> getRequiredExtensions();

        // Instance
        void createInstance();

        // Surface
        void createSurface();

        // Physical device
        void pickPhysicalDevice();
        int32_t rateDeviceSuitability(vk::PhysicalDevice device);
        bool isDeviceSuitable(vk::PhysicalDevice device, const vk::PhysicalDeviceProperties* deviceProperties, const vk::PhysicalDeviceFeatures* deviceFeatures);
        bool checkDeviceExtensionSupport(vk::PhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device);

        // Logical device
        void createLogicalDevice();

        // Swap chain
        SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice device);
        vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
        vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
        vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();
        void createImageViews();

        void createGraphicsPipeline();

        static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
            vk::DebugUtilsMessageSeverityFlagsEXT messageSeverity,
            vk::DebugUtilsMessageTypeFlagsEXT messageType,
            const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
    };
} // namespace engine


#endif // _VULKAN_MANAGER_HPP_