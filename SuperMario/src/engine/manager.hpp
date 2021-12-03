#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

namespace engine {
    class manager {
    public:
        manager() = default;
        virtual ~manager() = default;
        virtual void run() = 0;
    };
} // namespace engine


#endif // _MANAGER_HPP_