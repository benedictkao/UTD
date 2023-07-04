#pragma once

#include <cstddef>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory> // allocator

namespace utd {

  template <class T> //, class Allocator = std::allocator<T>>
  class vector {

  private:
    size_t vector_head = 0;
    size_t vector_size = 0;

    T*           capacity_head = nullptr;
    size_t       capacity;
    const size_t capacity_resize_rate = 2;
    const size_t min_capacity         = 12;

    void init_capacity(size_t size) {
      capacity      = max(size, min_capacity);
      capacity_head = new T[max(size, min_capacity)];
    }

    void init_vector(const size_t size) {
      if (capacity_head == nullptr)
        init_capacity(size);

      vector_size = size;
      vector_head = 0;
    }

    size_t static min(size_t a, size_t b) {
      if (a < b)
        return a;
      return b;
    }

    size_t static max(size_t a, size_t b) {
      if (a > b)
        return a;
      return b;
    }


  public:
    class VectorEmptyErr {};
    class ResizeCapacityErr {};
    class IdxOutOfRange {};

    // Destructors
    ~vector() { delete[] capacity_head; }

    // Constructors
    // TODO: list initialiser
    vector() { init_vector(0); }

    vector(size_t size) { init_vector(size); }

    vector(size_t size, const T const_val) {
      init_vector(size);

      for (int i = 0; i < size; i++) {
        capacity_head[vector_head + i] = const_val;
      }
    }

    // NOT WORKING
    /*
    template <class InputIterator>
    vector(InputIterator first, InputIterator last) {
      init_vector(0);
      size_t dist  = last - first;
      size_t count = 0;
      while (first != last) {
        push_back(*first);
        count++;
      }
    }
    */

    // copy constructor
    vector(vector& target_vector) {
      init_vector(0);

      for (int i = 0; i < target_vector.size(); i++) {
        push_back(target_vector[i]);
      }
    };

    // move constructor
    // TODO: steal the resources
    vector(vector&& target_vector) {
      init_vector(0);

      for (int i = 0; i < target_vector.size(); i++)
        push_back(target_vector[i]);

      target_vector.clear();
    };

    // Methods
    void push_back(T new_item) {
      if (vector_head + vector_size == capacity) {
        reserve(capacity * capacity_resize_rate);
      }

      capacity_head[vector_head + vector_size] = new_item;
      vector_size++;
    };

    size_t size() { return vector_size; };

    T* begin() { return capacity_head + vector_head; }

    T* end() {
      return vector_size > 0 ? capacity_head + vector_head + vector_size - 1 :
                               capacity_head + vector_head;
    }

    void pop() {
      if (vector_size == 0)
        throw VectorEmptyErr();

      vector_size--;
      vector_head++;
    }

    void pop_back() {
      if (vector_size == 0)
        throw VectorEmptyErr();

      vector_size--;
    }


    T at(size_t idx) {
      if (idx < 0 || idx >= vector_size) {
        throw IdxOutOfRange();
      }

      return capacity_head[vector_head + idx];
    }

    // TODO: does clear resizes the inner array
    void clear() {
      memset(capacity_head, 0, sizeof(T) * capacity);
      init_vector(0);
    }

    void reserve(size_t new_capacity) {
      if (new_capacity == capacity)
        return;

      T* new_capacity_head;
      // TODO: undefined behaviour, will it actually throw if memory alloc fails
      // TODO: Do we need this ?
      if (nullptr == (new_capacity_head = new T[new_capacity])) {
        throw ResizeCapacityErr();
      }

      memcpy(new_capacity_head,
             capacity_head + vector_head,
             sizeof(T) * min(vector_size, new_capacity));

      delete[] capacity_head;

      capacity_head = new_capacity_head;
      capacity      = new_capacity;
      vector_head   = 0;
      vector_size   = min(vector_size, new_capacity);
    }

    void resize(size_t new_size) {
      // delete everything after new_size
      if (new_size < vector_size) {
        memset(capacity_head + vector_head + vector_size,
               0,
               sizeof(T) * (vector_size - new_size));

        vector_size = new_size;
        if (vector_size * 2 < capacity) {
          reserve((capacity + 1) / capacity_resize_rate);
        }
      } else if (new_size > vector_size) {
        resize(new_size, 0);
      }
    }

    void resize(size_t new_size, T value) {
      if (new_size > vector_size) {
        for (int i = vector_size; i < new_size; i++) {
          push_back(value);
        }
      }
    }


    // operators
    T operator[](size_t index) {
      if (index >= vector_size || index < 0)
        throw IdxOutOfRange();

      return capacity_head[vector_head + index];
    };
  };

} // namespace utd
