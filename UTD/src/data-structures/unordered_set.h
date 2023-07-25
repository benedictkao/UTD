#pragma once

#include "../utils/hash.h"
#include <cstring>  // need this for memcpy
#include <iostream> // Remove after testing
#include <cmath>   // TODO: remove this

namespace utd {
  template <typename T>
  struct node {
    T        value;
    node<T>* next;

    node(const T& val) : next(nullptr) { memcpy(&value, &val, sizeof(T)); }
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

    linked_list() : head(nullptr) {}

    void clear() {
      node_ptr curr_ptr = head;
      while (curr_ptr) {
        node_ptr next = curr_ptr->next;
        delete curr_ptr;
        curr_ptr = next;
      }
    }
  };

  template <typename T>
  class unordered_set {
  private:
    typedef node<T>*        node_ptr;
    static constexpr size_t DEFAULT_BUCKET_COUNT{ 10 };
    static constexpr int    EXPAND_SIZE_MULTIPLIER{ 2 };
    static constexpr float  DEFAULT_MAX_LOAD_FACTOR{ 1.0 };

    size_t _num_elements; // number of elements stored in the set currently
    size_t _bucket_count; // size of _buckets
    linked_list<T>* _buckets;

    /*
     * Load factor is the _num_elements / _bucket_count. Max load factor is the
     * maximum value of load factor before resizing has to happen
     */
    float _max_load_factor = DEFAULT_MAX_LOAD_FACTOR;

    size_t getRequiredBucketCount(size_t size) const {
      // TODO: remove use of std::ceil
      const float req_buckets_float = ceil(size * _max_load_factor);
      return static_cast<size_t>(req_buckets_float);
    }

    void insertElement(node_ptr& bucket_node_ref, const T& item) {
      bucket_node_ref = new node(item);
      _num_elements++;
    }

    void changeBucketCount(size_t new_bucket_count) {
      linked_list<T>* new_buckets = new linked_list<T>[new_bucket_count]();

      // moving data from old buckets to new buckets, can't use memcpy because
      // rehashing is needed
      for (int i = 0; i < _bucket_count; i++) {
        node_ptr* curr_ptr_addr = &(_buckets[i].head);

        // iterate over every node in old bucket
        while (*curr_ptr_addr) {
          const size_t hashed_index     = utd::hash<T>((*curr_ptr_addr)->value);
          const size_t new_bucket_index = hashed_index % new_bucket_count;

          // get last pointer address of new bucket
          node_ptr* last_ptr_addr = &(new_buckets[new_bucket_index].head);
          while (*last_ptr_addr)
            last_ptr_addr = &((*last_ptr_addr)->next);

          // point last pointer of new bucket to existing node in old bucket
          *last_ptr_addr = *curr_ptr_addr;

          // iterate to next node in old bucket
          curr_ptr_addr = &((*curr_ptr_addr)->next);

          // last node in new bucket should not point to anything
          (*last_ptr_addr)->next = nullptr;
        }
      }

      delete[] _buckets;
      _buckets      = new_buckets;
      _bucket_count = new_bucket_count;
    }

  public:
    unordered_set() : _num_elements(0), _bucket_count(DEFAULT_BUCKET_COUNT) {
      _buckets = new linked_list<T>[DEFAULT_BUCKET_COUNT]();
    }

    ~unordered_set() {
      for (int i = 0; i < _bucket_count; i++)
        _buckets[i].clear();
      delete[] _buckets;
    }

    // TODO: add copy assignment and move assignment + constructor

    // TODO: in cpp standard this returns size_type (usually a typedef for
    // size_t, but should look into this)
    size_t bucket_count() const noexcept { return _bucket_count; }

    float max_load_factor() const noexcept { return _max_load_factor; }

    void max_load_factor(float load_factor) { _max_load_factor = load_factor; }

    /*
     * Does nothing if new load factor is smaller than max load factor
     */
    void reserve(size_t size) {
      const size_t req_buckets = getRequiredBucketCount(size);
      if (req_buckets > _bucket_count)
        changeBucketCount(req_buckets);
    }

    /*
     * Creates a copy of the item and inserts it into the set
     */
    void insert(T item) { // TODO: should return pair<iterator,bool>
      const size_t req_buckets = getRequiredBucketCount(_num_elements + 1);
      if (req_buckets > _bucket_count)
        changeBucketCount(_bucket_count * EXPAND_SIZE_MULTIPLIER);

      const size_t    hashed_index = utd::hash<T>(item);
      const size_t    bucket_index = hashed_index % _bucket_count;
      linked_list<T>& bucket       = _buckets[bucket_index];

      node_ptr* curr_ptr_addr = &(bucket.head);
      while (*curr_ptr_addr) {
        if ((*curr_ptr_addr)->value == item)
          return;
        curr_ptr_addr = &((*curr_ptr_addr)->next);
      }
      insertElement(*curr_ptr_addr, item);

      /* Broken Example */
      // node_ptr curr_ptr = bucket.head;  -> broken here because copy assigning
      // new dangling pointer while (curr_ptr) {
      //   if (curr_ptr->value == item)
      //     return;
      //   curr_ptr = curr_ptr->next;
      // }
      // insertElement(curr_ptr, item);
    }

    // TODO: add move insert overload

    // Test function - remove when done
    void print_buckets() {
      std::cout << '[';
      for (int i = 0; i < _bucket_count; i++) {
        node<T>* curr = _buckets[i].head;
        while (curr) {
          std::cout << curr->value << ',';
          curr = curr->next;
        }
      }
      std::cout << ']' << '\n';
    }
  };
} // namespace utd