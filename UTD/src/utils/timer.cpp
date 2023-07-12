#include "timer.h"

#include <iostream>

void utils::print_interval(
    chrono_time start_time,
    chrono_time end_time,
    UNIT_TIME u_t
) {
    switch (u_t) {
        case MICRO_SEC: {
            const auto interval = std::chrono::duration_cast<
                std::chrono::microseconds>(end_time - start_time);

            std::cout << "Time Reading: " << interval.count()
                << " microseconds"
                << "\n";
            break;
        };
        case MILLI_SEC: {
            const auto interval = std::chrono::duration_cast<
                std::chrono::milliseconds>(end_time - start_time);

            std::cout << "Time Reading: " << interval.count()
                << " milliseconds"
                << "\n";
        }
        case SEC: {
            const auto interval =
                std::chrono::duration_cast<std::chrono::seconds>(
                    end_time - start_time);

            std::cout << "Time Reading: " << interval.count()
                << " seconds"
                << "\n";
        }
        default: {
            const auto interval = std::chrono::duration_cast<
                std::chrono::microseconds>(end_time - start_time);

            std::cout << "Time Reading: " << interval.count()
                << " microseconds"
                << "\n";
        }
    }
}

void utils::Timer::start_from_zero() {
    start_time_ = std::chrono::steady_clock::now();
    end_time_ = std::chrono::steady_clock::now();
}

utils::Timer::Timer() { start_from_zero(); }

void utils::Timer::stop() { end_time_ = std::chrono::steady_clock::now(); }

void utils::Timer::print_reading(UNIT_TIME u_t) {
    print_interval(start_time_, end_time_, u_t);
}

void utils::time(void_func func, UNIT_TIME u_t) {
    std::chrono::time_point<std::chrono::steady_clock> start_time =
        std::chrono::steady_clock::now();

    func();

    std::chrono::time_point<std::chrono::steady_clock> end_time =
        std::chrono::steady_clock::now();

    print_interval(start_time, end_time, u_t);
};

utils::Timer_raii::Timer_raii(UNIT_TIME u_t) {
    start_time_ = chrono_clock::now();
    u_t_ = u_t;
}

utils::Timer_raii::~Timer_raii() {
    chrono_time end_time_ = chrono_clock::now();
    print_interval(start_time_, end_time_, u_t_);
}

static void time_function(void (*func)()) {
    std::cout << "TIMER METHOD"
        << "\n";

    utils::time(func, utils::MICRO_SEC);
}

static void time_manual(void (*func)()) {
    std::cout << "TIMER CLASS METHOD"
        << "\n";

    utils::Timer clock_watch;
    clock_watch.start_from_zero();

    func();

    clock_watch.stop();
    clock_watch.print_reading(utils::MICRO_SEC);
}

static void time_raii(void (*func)()) {
    std::cout << "TIMER CLASS RAII METHOD"
        << "\n";

    utils::Timer_raii timer_raii(utils::UNIT_TIME::MICRO_SEC);
    func();
}

void utils::time(void_func func, TIMER_METHOD method) {
    switch (method) {
    case TIMER_METHOD::FUNCTION:
        time_function(func);
        break;
    case TIMER_METHOD::MANUAL:
        time_manual(func);
        break;
    case TIMER_METHOD::RAII:
        time_raii(func);
        break;
    }
}