#ifndef _OLD_MANAGER_HPP_
#define _OLD_MANAGER_HPP_

namespace engine {
    class old_manager {
    public:
        old_manager() = default;
        virtual ~old_manager() = default;
        virtual void run() = 0;
    };
} // namespace engine


#endif // _OLD_MANAGER_HPP_