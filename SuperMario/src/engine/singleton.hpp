#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

namespace engine {
    template<class T>
    class singleton {
    private:
        static std::shared_ptr<T> _instance;
    public:
        static inline std::shared_ptr<T> get() {
            if (_instance == nullptr) {
                _instance = std::make_shared<T>();
            }
            return _instance;
        };
    };

    template<class T>
    std::shared_ptr<T> singleton<T>::_instance = nullptr;
} // namespace engine


#endif // _SINGLETON_HPP_