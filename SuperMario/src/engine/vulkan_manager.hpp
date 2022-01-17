#ifndef _VULKAN_MANAGER_HPP_
#define _VULKAN_MANAGER_HPP_

#include "manager.hpp"
#include "queue_family_indices.hpp"
#include "glfw_manager.hpp"

namespace engine {
    class vulkan_manager : public manager {
    private:
        std::string _application_name;
        std::shared_ptr<glfw_manager> _glfw_manager;

        vk::Instance _instance;

        const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        std::vector<vk::ExtensionProperties> _extensions;

        vk::DebugUtilsMessengerEXT _debugMessenger;

        vk::SurfaceKHR _surface;

        vk::PhysicalDevice _physicalDevice;

        vk::Device _device;

        vk::Queue _graphicsQueue;
        vk::Queue _presentQueue;

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
        bool checkValidationLayerSupport();

        std::vector<const char*> getRequiredExtensions();
        bool checkExtensionSupport(const std::vector<const char*>& extensions);

        void createInstance();

        void createSurface();

        void setupDebugCallback();

        void pickPhysicalDevice();
        int32_t rateDeviceSuitability(vk::PhysicalDevice device);
        bool isDeviceSuitable(vk::PhysicalDevice device, const vk::PhysicalDeviceProperties* deviceProperties, const vk::PhysicalDeviceFeatures* deviceFeatures);
        QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device);

        void createLogicalDevice();

        static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
            vk::DebugUtilsMessageSeverityFlagsEXT messageSeverity,
            vk::DebugUtilsMessageTypeFlagsEXT messageType,
            const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
    };
} // namespace engine


#endif // _VULKAN_MANAGER_HPP_