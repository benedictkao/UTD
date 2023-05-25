#include "Demo.h"

#include "../data-structures/Array.h"
#include "../utils/Timer.h"

static void run_array() {
    utd::array<int, 2> a;

    for (int i = 0; i < 10000; i++) {
        a[0] = 0;
        a[1] = 1;
    }
};

void demo::test_array() {
    utils::time(run_array);
}
