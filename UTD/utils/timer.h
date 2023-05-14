#pragma once

#include <chrono>
#include <iostream>
#include <string>

// Utility classes
namespace utils {

enum UNIT_TIME { MILLI_SEC = 1, MICRO_SEC = 2, SEC = 3 };

void print_interval(
    std::chrono::time_point<std::chrono::steady_clock> start_time,
    std::chrono::time_point<std::chrono::steady_clock> end_time,
    enum UNIT_TIME u_t) {
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

// Helper Timer Class using std::chrono
class Timer {
       private:
        std::chrono::time_point<std::chrono::steady_clock> start_time_;
        std::chrono::time_point<std::chrono::steady_clock> end_time_;

        void reset() {
                start_time_ = std::chrono::steady_clock::now();
                end_time_ = std::chrono::steady_clock::now();
        }

       public:
        Timer() { reset(); }

        void start() { reset(); }

        void stop() { end_time_ = std::chrono::steady_clock::now(); }

        void print_reading(enum UNIT_TIME u_t) {
                print_interval(start_time_, end_time_, u_t);
        }
};

// Helper Time function
void time(void (*func)(), enum UNIT_TIME u_t) {
        std::chrono::time_point<std::chrono::steady_clock> start_time =
            std::chrono::steady_clock::now();

        func();

        std::chrono::time_point<std::chrono::steady_clock> end_time =
            std::chrono::steady_clock::now();

        print_interval(start_time, end_time, u_t);
};

// Helper Timer Class RAII Style
class Timer_raii {
       public:
        Timer_raii(std::string helper_text, enum UNIT_TIME u_t) {
                std::cout << helper_text << std::endl;
                start_time_ = std::chrono::steady_clock::now();
                u_t_ = u_t;
        }

        ~Timer_raii() {
                std::chrono::time_point<std::chrono::steady_clock> end_time_ =
                    std::chrono::steady_clock::now();
                print_interval(start_time_, end_time_, u_t_);
        }

       private:
        std::chrono::time_point<std::chrono::steady_clock> start_time_;
        std::chrono::time_point<std::chrono::steady_clock> end_time_;
        enum UNIT_TIME u_t_;
};

}  // namespace utils
