#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include "engine/vulkan_manager.hpp"

namespace super_mario {

    class application {
    private:
        bool _running;

        std::unique_ptr<engine::vulkan_manager> _vulkan_manager = nullptr;
    public:
        application();
        ~application();

        void run();
    private:
    };

} // namespace super_mario


#endif // _APPLICATION_HPP_