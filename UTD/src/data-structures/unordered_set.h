#pragma once

namespace utd {
  template <typename T>
  struct node {
    T        value;
    node<T>* next;

    node(const T&);

    node(T&&);
  };

  /*
   * use lightweight class to store linked-list head. Allows for easy value
   * initialisation and helper function to delete all pointers in the list
   */
  template <typename T>
  struct linked_list { // TODO: can this be reused for map? If so, what should
                       // we name it?
    typedef node<T>* node_ptr;

    node_ptr head;

    linked_list();

    void clear();
  };

  template <typename T>
  class unordered_set {
  private:
    typedef node<T>* node_ptr;

    size_t _num_elements; // number of elements stored in the set currently
    size_t _bucket_count; // size of _buckets
    linked_list<T>* _buckets;

    /*
     * Load factor is the _num_elements / _bucket_count. Max load factor is the
     * maximum value of load factor before resizing has to happen
     */
    float _max_load_factor;

    size_t getRequiredBucketCount(size_t) const;

    void insertElement(node_ptr&, const T&);

    void insertElement(node_ptr&, T&&);

    void changeBucketCount(size_t);

    void copyBuckets(const unordered_set&);

  public:
    unordered_set();

    unordered_set(const unordered_set&);

    unordered_set(unordered_set&&);

    unordered_set& operator=(const unordered_set&);

    unordered_set& operator=(unordered_set&&);

    ~unordered_set();

    size_t size() const noexcept;

    // TODO: in cpp standard this returns size_type (usually a typedef for
    // size_t, but should look into this)
    size_t bucket_count() const noexcept;

    float max_load_factor() const noexcept;

    void max_load_factor(float load_factor);

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

#include "unordered_set.tpp"