// UTD.cpp : Defines the entry point for the application.

#include "UTD.h"

#include <unistd.h>

#include "utils/timer.h"

void main_test() {
        utd::array<int, 2> a;

        for (int i = 0; i < 10000; i++) {
                a.set(0, 0);
                a.set(1, 1);
        }
};

int main() {
        utd::array<int, 2> a;

        /* Timer class method */
        std::cout << "TIMER CLASS METHOD"
                  << "\n";

        utils::timer clock_watch;
        clock_watch.start();

        for (int i = 0; i < 10000; i++) {
                a.set(0, 0);
                a.set(1, 1);
        }

        clock_watch.stop();
        clock_watch.print_reading();

        std::cout << a.get(0) << ", " << a.get(1) << std::endl;

        /* Timer method */
        std::cout << "TIMER METHOD"
                  << "\n";

        utils::time(main_test);

        return 0;
};
