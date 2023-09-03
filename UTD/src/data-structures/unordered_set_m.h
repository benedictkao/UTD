#pragma once

namespace utd {
  template <typename T>
  struct node_m {
    T          value;
    node_m<T>* next = nullptr;
    node_m<T>* prev = nullptr;

    node_m();

    node_m(const T&);

    node_m(T&&);
  };

  /*
   * use lightweight class to store linked-list head. Allows for easy value
   * initialisation and helper function to delete all pointers in the list
   */
  template <typename T>
  struct base_node {
    node_m<T>* head = nullptr;
    node_m<T>* tail = nullptr;

    base_node();

    void clear();
  };

  template <typename T>
  class unordered_set_m {
  private:
    size_t _num_elements; // number of elements stored in the set currently
    size_t _bucket_count; // size of _buckets
    base_node<T>* _buckets = nullptr;
    node_m<T>     _head;

    /*
     * Load factor is the _num_elements / _bucket_count. Max load factor is the
     * maximum value of load factor before resizing has to happen
     */
    float _max_load_factor;

    // void insert_element(base_node<T>&, T&);
    void insert_element(base_node<T>*, T&);

    size_t get_req_bucket_count(size_t) const;

  public:
    unordered_set_m();

    ~unordered_set_m();

    const node_m<T>* begin();

    size_t size() const noexcept;

    // TODO: in cpp standard this returns size_type (usually a typedef for
    // size_t, but should look into this)
    size_t bucket_count() const noexcept;

    float max_load_factor() const noexcept;

    void max_load_factor(float);

    void rehash(size_t);

    /*
     * Does nothing if new load factor is smaller than max load factor
     */
    void reserve(size_t);

    /*
     * Creates a copy of the item and inserts it into the set
     */
    void insert(const T&);

    /*
     * Moves the item into the set
     */
    void insert(T&&);

    // Test function - remove when done
    void print_buckets();
  };
} // namespace utd

#include "unordered_set_m.tpp"