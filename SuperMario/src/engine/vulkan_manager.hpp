#ifndef _VULKAN_MANAGER_HPP_
#define _VULKAN_MANAGER_HPP_

#include "manager.hpp"

namespace engine {
    class vulkan_manager : public manager {
    private:
        std::string _application_name;

        VkInstance _instance;

        std::vector<VkExtensionProperties> _extensions;

        const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        VkDebugUtilsMessengerEXT _debugMessenger;

#ifdef NDEBUG
        const bool _enableDebugMode = false;
#else
        const bool _enableDebugMode = true;
#endif

    public:
        vulkan_manager(const std::string& application_name);
        virtual ~vulkan_manager() override;
    private:
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        bool checkExtensionSupport(const std::vector<const char*>& extensions);
        void createInstance();
        void setupDebugCallback();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );
    };
} // namespace engine


#endif // _VULKAN_MANAGER_HPP_