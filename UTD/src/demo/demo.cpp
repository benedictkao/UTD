#include "demo.h"

#include <iostream>

#include "../data-structures/array.h"
#include "../data-structures/string24.h"
#include "../data-structures/string32.h"
#include "../data-structures/unordered_set.h"
#include "../data-structures/unordered_set_m.h"
#include "../utils/timer.h"

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
  utd::string32 stack_string = "A stack string."; // size 15
  std::cout << stack_string << LINE_BRK;
  std::cout << " Size=" << stack_string.size() << LINE_BRK;
  void* cap_addr = (void*) ((char*) &stack_string +
                            16); // sizeof(_data) = 8, sizeof(_size) = 8
  std::cout << "capacity address=" << cap_addr
            << ", data address=" << (void*) stack_string.c_str() << LINE_BRK;

  utd::string32 heap_string = "A heap allocated string."; // size 24
  std::cout << heap_string << LINE_BRK;
  std::cout << " Size=" << heap_string.size() << LINE_BRK;
  cap_addr = (void*) ((char*) &heap_string + 16);
  std::cout << "capacity address=" << cap_addr
            << ", data address=" << (void*) heap_string.c_str() << LINE_BRK;

  std::cout << "stack string capacity before reserve   = "
            << stack_string.capacity() << LINE_BRK;
  stack_string.reserve(49);
  std::cout << "stack string capacity after reserve 49 = "
            << stack_string.capacity() << LINE_BRK;

  std::cout << "heap string capacity before reserve    = "
            << heap_string.capacity() << LINE_BRK;
  heap_string.reserve(15);
  std::cout << "heap string capacity after reserve 15  = "
            << heap_string.capacity() << LINE_BRK;
  heap_string.reserve(49);
  std::cout << "heap string capacity after reserve 49  = "
            << heap_string.capacity() << LINE_BRK;
}

void demo::demo_set() {
  utd::unordered_set<int> s;
  std::cout << "Insert 3" << LINE_BRK;
  s.insert(3);
  s.print_buckets();
  std::cout << "Size        : " << s.size() << LINE_BRK;
  std::cout << "Bucket count: " << s.bucket_count() << LINE_BRK << LINE_BRK;

  std::cout << "Insert 3" << LINE_BRK;
  s.insert(3);
  s.print_buckets();
  std::cout << "Size        : " << s.size() << LINE_BRK;
  std::cout << "Bucket count: " << s.bucket_count() << LINE_BRK << LINE_BRK;

  std::cout << "Insert 2147483647" << LINE_BRK;
  s.insert(2147483647);
  s.print_buckets();
  std::cout << "Size        : " << s.size() << LINE_BRK;
  std::cout << "Bucket count: " << s.bucket_count() << LINE_BRK << LINE_BRK;

  std::cout << "Insert -2147483648" << LINE_BRK;
  s.insert(-2147483648);
  s.print_buckets();
  std::cout << "Size        : " << s.size() << LINE_BRK;
  std::cout << "Bucket count: " << s.bucket_count() << LINE_BRK << LINE_BRK;

  std::cout << "Reserve 14" << LINE_BRK;
  s.reserve(14);
  s.print_buckets();
  std::cout << "Size        : " << s.size() << LINE_BRK;
  std::cout << "Bucket count: " << s.bucket_count() << LINE_BRK << LINE_BRK;

  std::cout << "Reserve 5" << LINE_BRK;
  s.reserve(5);
  s.print_buckets();
  std::cout << "Size        : " << s.size() << LINE_BRK;
  std::cout << "Bucket count: " << s.bucket_count() << LINE_BRK << LINE_BRK;

  auto s2(s);
  std::cout << "Copy constructor" << LINE_BRK;
  s2.print_buckets();
  std::cout << "Size        : " << s2.size() << LINE_BRK;
  std::cout << "Bucket count: " << s2.bucket_count() << LINE_BRK << LINE_BRK;

  auto s3 = s;
  std::cout << "Copy assignment" << LINE_BRK;
  s3.print_buckets();
  std::cout << "Size        : " << s3.size() << LINE_BRK;
  std::cout << "Bucket count: " << s3.bucket_count() << LINE_BRK;
}

void demo::demo_array_iterator() {
  utd::array<int, 5> arr = { 1, 2, 3 };
  for (int i : arr)
    std::cout << i << LINE_BRK;
}

void demo::demo_string24() {
  utd::string24 s = "hello";
  std::cout << s[0] << ',' << s[1] << LINE_BRK;
  std::cout << s << LINE_BRK;
  std::cout << s.size() << LINE_BRK;

  utd::string24 s2 = "this is a very very long stringggggg";
  std::cout << s2 << LINE_BRK;
  std::cout << s2.size() << LINE_BRK;

  utd::string24 s3;
  std::cout << s3.size() << LINE_BRK;
  s3 = s;
  std::cout << s3 << LINE_BRK;
  std::cout << s3.size() << LINE_BRK;
  s3 = s2;
  std::cout << s3 << LINE_BRK;
  std::cout << s3.size() << LINE_BRK;

  utd::string24 s4(s);
  std::cout << s4 << LINE_BRK;
  utd::string24 s5(s2);
  std::cout << s5 << LINE_BRK;

  utd::string24 s6 = s4 + "!!!!";
  std::cout << s6 << LINE_BRK;
  utd::string24 s7 = s6 + " This is no longer a small string";
  std::cout << s7 << LINE_BRK;
  utd::string24 s8 = s5 + "!!!!";
  std::cout << s8 << LINE_BRK;

  s += "..";
  std::cout << s << LINE_BRK;
  std::cout << s.size() << LINE_BRK;
  s += s2;
  std::cout << s << LINE_BRK;
  std::cout << s.size() << LINE_BRK;
}

void demo::demo_unordered_set_m() {
  {
    utd::unordered_set_m<int> s;

    s.insert(31);
    s.insert(43);

    s.insert(99);

    s.insert(1);

    s.insert(3);
  }

  {
    utd::unordered_set_m<int> s;
    s.max_load_factor(10.0);

    s.insert(31);
    s.insert(43);

    s.insert(99);

    s.insert(1);

    s.insert(3);

    const utd::node_m<int>* head = (s.begin());
    while (head) {
      std::cout << head->value << std::endl;
      head = head->next;
    }
  }
}
