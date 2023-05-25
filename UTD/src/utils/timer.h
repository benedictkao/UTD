#pragma once

#include <chrono>

// Utility classes
namespace utils {

    enum UNIT_TIME { MILLI_SEC = 1, MICRO_SEC = 2, SEC = 3 };
    enum TIMER_METHOD { FUNCTION, MANUAL, RAII };

    using chrono_clock = std::chrono::steady_clock;
    using chrono_time = std::chrono::time_point<chrono_clock>;
    using void_func = void (*)();

    void print_interval(chrono_time start_time, chrono_time end_time, UNIT_TIME u_t);

    void time(void_func func, TIMER_METHOD method = TIMER_METHOD::FUNCTION);

    // Helper Timer Class using std::chrono
    class Timer {

    private:
        chrono_time start_time_;
        chrono_time end_time_;

    public:
        Timer();

        void start_from_zero();

        void stop();

        void print_reading(UNIT_TIME u_t);
    };

    // Helper Time function
    void time(void_func func, UNIT_TIME u_t);

    // Helper Timer Class RAII Style
    class Timer_raii {

    private:
        chrono_time start_time_;
        chrono_time end_time_;
        UNIT_TIME u_t_;

    public:
        Timer_raii(UNIT_TIME u_t);

        ~Timer_raii();
    };

}  // namespace utils
