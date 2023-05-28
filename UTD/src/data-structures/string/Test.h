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

    void print_expect(size_t expected, size_t actual)
    {
        std::cout << "Expected [" << expected << "] - got [" << actual << "] \n";
    }

    void print_expect(char expected, char actual)
    {
        std::cout << "Expected [" << expected << "] - got [" << actual << "] \n";
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

        // base string
        std::string s("hello");

        // from c string
        char c[6] = "hello";
        string s1(c);

        print_expect(s1.size(), s.size());
        std::cout << "checkpoint 5 \n";

        print_expect(s1[2], s[2]);
        std::cout << "checkpoint 6 \n";

        s1 += s1;
        std::string s1_test("hellohello");
        print_expect(s1_test, s1);
        std::cout << "checkpoint 7 \n";

        string s2("hellohello");
        if (s2 == s1)
            std::cout << "true" << '\n';

        std::cout << "checkpoint 8 \n";
    };

    void string_test_suites()
    {
        string_constructor_test_suites();
        string_methods_test_suites();
    };
}