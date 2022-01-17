#ifndef _VULKAN_MANAGER_HPP_
#define _VULKAN_MANAGER_HPP_

#include "manager.hpp"
#include "queue_family_indices.hpp"

namespace engine {
    class vulkan_manager : public manager {
    private:
        std::string _application_name;

        vk::Instance _instance;

        std::vector<vk::ExtensionProperties> _extensions;

        const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        vk::DebugUtilsMessengerEXT _debugMessenger;

        vk::PhysicalDevice _physicalDevice;

#ifdef NDEBUG
        const bool _enableDebugMode = false;
#else
        const bool _enableDebugMode = true;
#endif

    public:
        vulkan_manager(const std::string& application_name);
        virtual ~vulkan_manager() override;
        virtual void run() override;
    private:
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        bool checkExtensionSupport(const std::vector<const char*>& extensions);
        void createInstance();
        void setupDebugCallback();
        void pickPhysicalDevice();
        bool isDeviceSuitable(vk::PhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device);

        static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
            vk::DebugUtilsMessageSeverityFlagsEXT messageSeverity,
            vk::DebugUtilsMessageTypeFlagsEXT messageType,
            const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
    };
} // namespace engine


#endif // _VULKAN_MANAGER_HPP_