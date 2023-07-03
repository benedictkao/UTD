#include "Demo.h"

#include <iostream>

#include "../data-structures/Array.h"
#include "../data-structures/String.h"
#include "../data-structures/String32.h"
#include "../utils/Timer.h"

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
    utd::string32 stack_string = "A short string.";                    // size 15
    utd::string32 heap_string = "A slightly longer string.";           // size 25
    utd::string32* p = &stack_string;
    utd::string32* p2 = &heap_string;
    std::cout << "Demo complete" << std::endl;
}