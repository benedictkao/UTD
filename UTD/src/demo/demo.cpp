#include "demo.h"

#include <iostream>

#include "../data-structures/array.h"
#include "../data-structures/string32.h"
#include "../utils/timer.h"
#include "../data-structures/unordered_set.h"

static constexpr char LINE_BRK{ '\n' };

static void run_array() {
    utd::array<int, 2> a;

    for (int i = 0; i < 10000; i++) {
        a[0] = 0;
        a[1] = 1;
    }
};

void demo::time_array() {
    utils::time(run_array);
}

void demo::demo_string32() {
    utd::string32 stack_string = "A stack string.";                    // size 15
    std::cout << stack_string << LINE_BRK;
    std::cout << " Size=" << stack_string.size() << LINE_BRK;
    void* cap_addr = (void*)((char*)&stack_string + 16);               // sizeof(_data) = 8, sizeof(_size) = 8
    std::cout << "capacity address=" << cap_addr
              << ", data address=" << (void *)stack_string.c_str() << LINE_BRK;

    utd::string32 heap_string = "A heap allocated string.";           // size 24
    std::cout << heap_string << LINE_BRK;
    std::cout << " Size=" << heap_string.size() << LINE_BRK;
    cap_addr = (void*)((char*)&heap_string + 16);
    std::cout << "capacity address=" << cap_addr
        << ", data address=" << (void*)heap_string.c_str() << LINE_BRK;

    std::cout << "stack string capacity before reserve   = " << stack_string.capacity() << LINE_BRK;
    stack_string.reserve(49);
    std::cout << "stack string capacity after reserve 49 = " << stack_string.capacity() << LINE_BRK;

    std::cout << "heap string capacity before reserve    = " << heap_string.capacity() << LINE_BRK;
    heap_string.reserve(15);
    std::cout << "heap string capacity after reserve 15  = " << heap_string.capacity() << LINE_BRK;
    heap_string.reserve(49);
    std::cout << "heap string capacity after reserve 49  = " << heap_string.capacity() << LINE_BRK;
}

void demo::demo_set() {
    utd::set<int> s;
    s.insert(3);
    s.insert(3);
    s.insert(2147483647);
    s.insert(-2147483648);
    s.print_buckets();
}
