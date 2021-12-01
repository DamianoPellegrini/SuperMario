#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

namespace engine {

    class application {
    private:
        std::string _title;
        uint32_t _width;
        uint32_t _height;
        bool _running;

        // GLFW
        GLFWwindow* _window;

        // Vulkan
        VkInstance _instance;
        std::vector<VkExtensionProperties> _extensions;
    public:
        application(std::string title, uint32_t window_width, uint32_t window_height);
        ~application();

        void run();
    private:
        void initGLFW();
        void initVulkan();

        void mainLoop();

        void cleanupGLFW();
        void cleanupVulkan();
    };

} // namespace engine


#endif // _APPLICATION_HPP_