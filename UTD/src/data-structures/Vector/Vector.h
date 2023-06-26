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
    T*     vector_head = nullptr;
    size_t vector_size = 0;

    T*     capacity_head        = nullptr;
    size_t capacity             = 0;
    size_t capacity_resize_rate = 2;

    void init_capacity(size_t size) {
      capacity      = size;
      capacity_head = new T[size];
    }

    void init_vector(size_t size) {
      if (capacity_head == nullptr)
        init_capacity(size);

      vector_size = size;
      vector_head = capacity_head;
    }

    class VectorEmptyErr {};
    class ResizeCapacityErr {};
    class IdxOutOfRange {};

  public:
    size_t static min(size_t a, size_t b) {
      if (a < b)
        return a;
      return b;
    }

    // Destructors
    ~vector() { delete[] vector_head; }

    // Constructors
    vector() { init_vector(0); }

    vector(size_t size) {
      std::cout << "called size" << std::endl;
      init_vector(size);
    }

    vector(size_t size, const T const_val) {
      std::cout << "called size, val" << std::endl;
      init_vector(size);

      for (int i = 0; i < size; i++) {
        vector_head[i] = const_val;
      }
    }

    template <class InputIterator>
    vector(InputIterator* first, InputIterator* last) {
      std::cout << "call iterator" << std::endl;

      size_t        size = 0;
      InputIterator temp = first;
      while (temp != last) {
        size++;
        temp++;
      }

      init_vector(size);

      while (first != last) {
        push_back(*first);
        first++;
      }
    }

    // copy constructor
    vector(const vector& target_vector) {
      init_vector(target_vector.size());

      for (int i = 0; i < target_vector.size(); i++)
        push_back(target_vector[i]);
    };

    // move constructor
    vector(vector&& target_vector) {
      init_vector(target_vector.size());

      for (int i = 0; i < target_vector.size(); i++)
        push_back(target_vector[i]);

      target_vector.clear();
    };

    // Methods
    void push_back(T new_item) {
      if (vector_size == capacity) {
        reserve(capacity * capacity_resize_rate);
      }

      vector_head[vector_size++] = new_item;
    };

    size_t size() { return vector_size; };

    T* begin() { return vector_head; }

    T* end() { return vector_head + vector_size; }

    void pop() {
      if (vector_size == 0)
        throw VectorEmptyErr();

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

      return vector_head[idx];
    }

    void clear() {
      memset(vector_head, 0, sizeof(T) * vector_size);
      init_vector(0);
    }

    void reserve(size_t new_capacity) {
      if (new_capacity == capacity)
        return;

      T* new_capacity_head;
      if (nullptr == (new_capacity_head = new T[new_capacity])) {
        throw ResizeCapacityErr();
      }

      memcpy(new_capacity_head,
             vector_head,
             sizeof(T) * min(vector_size, new_capacity));

      delete[] capacity_head;

      capacity_head = new_capacity_head;
      capacity      = new_capacity;
      vector_head   = new_capacity_head;
      vector_size   = min(vector_size, new_capacity);
    }

    void resize(size_t new_size) {
      // delete everything after new_size
      for (int i = new_size; i < vector_size; i++) {
        delete vector_head[i];
      }

      vector_size = new_size;

      if (vector_size < (capacity + 1) / capacity_resize_rate)
        reserve((capacity + 1) / capacity_resize_rate);
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

      return vector_head[index];
    };
  };

} // namespace utd
