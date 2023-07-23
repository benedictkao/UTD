#pragma once

#include "../utils/hash.h"
#include <cstring>  // need this for memcpy
#include <iostream> // Remove after testing

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
  struct linked_list {
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
  class set {
  private:
    typedef node<T>*        node_ptr;
    static constexpr size_t DEFAULT_BUCKET_COUNT{ 10 };

    size_t _num_elements; // number of elements stored in the set currently
    size_t _bucket_count; // size of _buckets
    linked_list<T>* _buckets;

    void insertElement(node_ptr& bucket_node_ref, const T& item) {
      bucket_node_ref = new node(item);
      _num_elements++;
    }

  public:
    set() : _num_elements(0), _bucket_count(DEFAULT_BUCKET_COUNT) {
      _buckets = new linked_list<T>[DEFAULT_BUCKET_COUNT]();
    }

    ~set() {
      for (int i = 0; i < _bucket_count; i++)
        _buckets[i].clear();
      delete[] _buckets;
    }

    // TODO: add copy assignment and move assignment + constructor

    void reserve(size_t new_size) {
      _bucket_count = new_size;

      linked_list<T>* _new_buckets = new linked_list<T>[_bucket_count]();
      memcpy(_new_buckets, _buckets, sizeof(linked_list<T>) * _bucket_count);
      delete[] _buckets;
      _buckets = _new_buckets;
    }

    /*
     * Creates a copy of the item and inserts it into the set
     */
    void insert(T item) { // TODO: should return pair<iterator,bool>
      if (_num_elements == _bucket_count) {
        reserve(_bucket_count * 2);
      }

      const size_t    hashed_index = utd::hash<T>(item);
      const size_t    bucket_index = hashed_index % _bucket_count;
      linked_list<T>& bucket       = _buckets[bucket_index];

      // TODO: any way to improve below code to reduce branching?
      if (!bucket.head) {
        insertElement(bucket.head, item);
      } else {
        node_ptr curr_ptr = bucket.head;
        while (true) {
          if (curr_ptr->value == item) {
            // item already exists, don't do anything
            return;
          } else if (curr_ptr->next) {
            // iterate to next node
            curr_ptr = curr_ptr->next;
          } else {
            // reached end of the list
            insertElement(curr_ptr->next, item);
            return;
          }
        }
      }
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