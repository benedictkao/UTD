// UTD.cpp : Defines the entry point for the application.

#include "Demo.h"

#include <iostream>

#include "../data-structures/Array.h"
#include "../utils/timer.h"

namespace utd {

    static void test_code() {
        utd::array<int, 2> a;

        for (int i = 0; i < 10000; i++) {
            a[0] = 0;
            a[1] = 1;
        }
    };

    void utd::test_with_timer_class() {
        std::cout << "TIMER CLASS METHOD"
            << "\n";

        utils::Timer clock_watch;
        clock_watch.start();

        test_code();

        clock_watch.stop();
        clock_watch.print_reading(utils::MICRO_SEC);
    }

    void utd::test_with_time_method() {
        std::cout << "TIMER METHOD"
            << "\n";

        utils::time(test_code, utils::MICRO_SEC);
    }

    void utd::test_with_timer_class_raii() {
        std::cout << "TIMER CLASS RAII METHOD"
            << "\n";

        utils::Timer_raii timer_raii("Testing set array", utils::MICRO_SEC);
        test_code();
    }
}