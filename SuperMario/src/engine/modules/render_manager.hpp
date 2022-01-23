#ifndef _RENDER_MANAGER_HPP_
#define _RENDER_MANAGER_HPP_

#include "manager.hpp"
#include "singleton.hpp"

namespace engine {

    struct render_manager_config {
        std::string title;
    };

    class render_manager
        : public manager<render_manager_config>,
        public singleton<render_manager> {
    private:
        render_manager_config _config;

    public:
        virtual void init(render_manager_config config) final override;
        virtual void shutdown() final override;
    };
} // namespace engine

#endif // _RENDER_MANAGER_HPP_
