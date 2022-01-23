#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

namespace engine {
    class logger {
    public:
        static void init(std::string name);
        static void shutdown();
    };
} // namespace engine

#endif // _LOGGER_HPP_