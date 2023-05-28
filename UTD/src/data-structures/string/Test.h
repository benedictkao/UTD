#include <string.h>
#include "String.h"
#include <cassert>
#include <iostream>

#define assertm(exp, msg) assert(((void)msg, exp))

namespace utd
{
    using utd::string;

    void print_expect(std::string expected, utd::string actual)
    {
        std::cout << "Expected [" << expected.c_str() << "] - got [" << actual.c_str() << "] \n";
    }

    void string_constructor_test_suites()
    {
        std::cout << "Start constructor test suites \n";

        // default
        string();
        std::cout << "checkpoint 1 \n";

        // base string
        std::string s("hello");

        // from c string
        char c[6] = "hello";
        string s1(c);
        print_expect(s, s1);
        std::cout << "checkpoint 2 \n";

        // from utd::string / Copy Constructor
        string s2(s1);
        print_expect(s, s2);
        std::cout << "checkpoint 3 \n";

        // Move Constructor
        // TODO: How to test

        // from iterator
        std::string str(c);
        string s3(str.begin(), str.end());
        print_expect(s, s3);
        std::cout << "checkpoint 4 \n";
    };

    void string_methods_test_suites()
    {
        std::cout << "TEST Methods";
    };

    void string_test_suites()
    {
        string_constructor_test_suites();
        string_methods_test_suites();
    };
}