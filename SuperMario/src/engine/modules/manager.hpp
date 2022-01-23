#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

namespace engine {
    
    template<class ... InitParams>
    class manager {
    protected:
        bool _initialized;
    public:
        virtual void init(InitParams ... params) = 0;
        virtual void shutdown() = 0;

        inline bool is_initialized() const { return _initialized; }
    };
} // namespace engine


#endif // _MANAGER_HPP_