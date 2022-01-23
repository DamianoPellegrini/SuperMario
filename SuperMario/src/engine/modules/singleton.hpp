#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

namespace engine {
    template<class T>
    class singleton {
    private:
        static T* _instance;
    public:
        static inline T* get() {
            if (_instance == nullptr) {
                _instance = new T();
            }
            return _instance;
        };
    };

    template<class T>
    T* singleton<T>::_instance = nullptr;
} // namespace engine


#endif // _SINGLETON_HPP_