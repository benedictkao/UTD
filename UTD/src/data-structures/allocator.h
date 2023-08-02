#include <cstddef>

/*
Allocator

# Videos to watch / Things to readh
1. Traits of Allocators - https://www.youtube.com/watch?v=kSWfushlvB8
2. Implement Allocators - https://www.youtube.com/watch?v=LIb3L4vKZ7U
3. Move Assignment for Allocators -
https://stackoverflow.com/questions/27471053/example-usage-of-propagate-on-container-move-assignment

# Tools
1. MacOS - Check for mem leaks -
https://dr-rost.medium.com/detect-memory-leaks-on-macos-4cf257529aa


// API
Blk allocate
void deallocate

// Extra
static constexpr unsigned alignment;
static constexpr good_size(size_t);
bool owns(Blk);

*/

/* Basic Version */
namespace utd {

  template <class T>
  class BasicAllocator {

    typedef T value_type;

    // convert an allocator<T> to allocator<U>
    template <typename U>
    struct rebind {
      typedef BasicAllocator<U> other;
    };

  private:
  public:
    BasicAllocator(){};

    ~BasicAllocator(){};

    // Copy constructor
    template <class U>
    BasicAllocator(const BasicAllocator<U>&) noexcept;

    value_type* allocate(size_t);

    void deallocate(T*, size_t);
  };

  template <class T>
  T* BasicAllocator<T>::allocate(size_t const num_of_bytes) {
    return static_cast<T*>(::operator new(num_of_bytes));
  }

  template <class T>
  void BasicAllocator<T>::deallocate(T* p, size_t num_of_bytes) {
    if (p) {
      ::operator delete(p, num_of_bytes);
    }
  }

}; // namespace utd