#include "Demo.h"

#include <iostream>

#include "../data-structures/Array.h"
#include "../data-structures/String.h"
#include "../data-structures/String32.h"
#include "../utils/Timer.h"

static constexpr char new_line{ '\n' };

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

void demo::demo_string() {
    utd::string s = "A string";                             // move assignment
    std::cout << "Init string    : " << s << std::endl;

    utd::string s2 = s;                                     // copy assignment
    std::cout << "Copy string    : " << s2 << std::endl;

    utd::string s3 = std::move(s);
    std::cout << "Move string    : " << s3 << std::endl;

    s2[0] = 'a';
    std::cout << "Change char    : " << s2 << std::endl;

    s = "This is ";                                         // move assignment
    s3 = s + s2;                                            // move assignment
    std::cout << "+ string       : " << s3 << std::endl;

    s3 += " demo";
    std::cout << "+= string      : " << s3 << std::endl;

    s3 = s3 + '?';
    std::cout << "+ char         : " << s3 << std::endl;

    s3 += '!';
    std::cout << "+= char        : " << s3 << std::endl;

    s = s3.substr(8, 8);
    std::cout << "Substring      : " << s << std::endl;

    std::cout << "Comparison 1   : " << s << " == " << s2 << " = " << (s == s2) << std::endl;
    std::cout << "Comparison 2   : " << s << " == " << s3 << " = " << (s == s3) << std::endl;
}

void demo::demo_string32() {
    utd::string32 stack_string = "A stack string.";                    // size 15
    std::cout << stack_string << new_line;
    std::cout << " Size=" << stack_string.size() << new_line;
    void* cap_addr = (void*)((char*)&stack_string + 16);               // sizeof(_data) = 8, sizeof(_size) = 8
    std::cout << "capacity address=" << cap_addr
              << ", data address=" << (void *)stack_string.c_str() << new_line;

    utd::string32 heap_string = "A heap allocated string.";           // size 24
    std::cout << heap_string << new_line;
    std::cout << " Size=" << heap_string.size() << new_line;
    cap_addr = (void*)((char*)&heap_string + 16);
    std::cout << "capacity address=" << cap_addr
        << ", data address=" << (void*)heap_string.c_str() << new_line;

    std::cout << "stack string capacity before reserve   = " << stack_string.capacity() << new_line;
    stack_string.reserve(49);
    std::cout << "stack string capacity after reserve 49 = " << stack_string.capacity() << new_line;

    std::cout << "heap string capacity before reserve    = " << heap_string.capacity() << new_line;
    heap_string.reserve(15);
    std::cout << "heap string capacity after reserve 15  = " << heap_string.capacity() << new_line;
    heap_string.reserve(49);
    std::cout << "heap string capacity after reserve 49  = " << heap_string.capacity() << new_line;
}