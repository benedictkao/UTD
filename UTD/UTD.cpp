// UTD.cpp : Defines the entry point for the application.
//
#include <unistd.h>

#include "UTD.h"
#include "utils/timer.h"

int main()
{
        utd::array<int, 2> a;

        utils::timer clock_watch;

        clock_watch.start();
        // sleep(1); // for testing watch

        for (int i = 0; i < 10000; i++)
        {
                a.set(0, 0);
                a.set(1, 1);
        }

        clock_watch.stop();

        std::cout << a.get(0) << ", " << a.get(1) << std::endl;

        clock_watch.print_reading();

        return 0;
}
