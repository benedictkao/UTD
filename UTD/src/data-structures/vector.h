namespace utd {
  template <class T> //, class Allocator = std::allocator<T>>
  class vector {

  private:
    static constexpr size_t DEFAULT_VECTOR_CAPACITY{ 0 };
    static constexpr int    CAPACITY_RESIZE_RATE{ 2 };

    size_t _size;
    size_t _capacity;
    T*     _inner_array;

    // TODO: can this be a util method and take in iterator start and end?
    // Can be reused for set and map
    void fill(const T&, size_t, size_t);

  public:
    class VectorEmptyErr {};
    class ResizeCapacityErr {};
    class IdxOutOfRange {};

    // Destructors
    ~vector();

    // Constructors
    vector();

    vector(size_t);

    vector(size_t, const T&);

    // copy constructor
    vector(const vector&);

    // move constructor
    vector(vector&&) noexcept;

    // copy assignment
    vector& operator=(const vector&);

    // move assignment
    vector& operator=(vector&&);

    // Methods
    void push_back(const T&);

    void push_back(T&&);

    size_t size() const noexcept;

    T* begin();

    T* end();

    void pop_back();

    T at(size_t);

    /*
     * Does not change the capacity
     */
    void clear();

    void reserve(size_t);

    void resize(size_t);

    void resize(size_t, const T&);

    // operators
    T operator[](size_t);
  };
} // namespace utd

#include "vector.tpp"