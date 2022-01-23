#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

namespace super_mario {

    class application {
    private:
        bool _running;
    public:
        application();
        ~application();

        void run();
    private:
    };

} // namespace super_mario


#endif // _APPLICATION_HPP_