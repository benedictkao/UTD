#include "../utils/hash.h"
#include <math.h>

template <typename T>
utd::node_m<T>::node_m() : next(nullptr), prev(nullptr){};

template <typename T>
utd::node_m<T>::node_m(const T& v) : value(v), next(nullptr), prev(nullptr){};

template <typename T>
utd::node_m<T>::node_m(T&& v) : value(v), next(nullptr), prev(nullptr){};


template <typename T>
utd::base_node<T>::base_node(){};

template <typename T>
void utd::base_node<T>::clear() {
  node_m<T>* curr = head;

  while (curr && curr != tail) {
    node_m<T>* next_curr = curr->next;
    delete curr;
    curr = next_curr;
  }

  if (curr)
    delete curr;
}


constexpr size_t DEFAULT_BUCKET_COUNT_M = 1.0;
constexpr float  MIN_LOAD_FACTOR        = 1.0;
constexpr float  DEFAULT_LOAD_FACTOR    = 1.0;

template <typename T>
utd::unordered_set_m<T>::unordered_set_m()
    : _bucket_count(DEFAULT_BUCKET_COUNT_M)
    , _max_load_factor(DEFAULT_LOAD_FACTOR)
    , _num_elements(0) {
  _buckets = new base_node<T>[DEFAULT_BUCKET_COUNT_M];
};

template <typename T>
utd::unordered_set_m<T>::~unordered_set_m() {
  for (int i = 0; i < _bucket_count; ++i)
    _buckets[i].clear();

  delete[] _buckets;
};

template <typename T>
size_t utd::unordered_set_m<T>::size() const noexcept {
  return _num_elements;
};

template <typename T>
size_t utd::unordered_set_m<T>::bucket_count() const noexcept {
  return _bucket_count;
};

template <typename T>
float utd::unordered_set_m<T>::max_load_factor() const noexcept {
  return _max_load_factor;
};

template <typename T>
void utd::unordered_set_m<T>::max_load_factor(float new_max_load_factor) {
  if (new_max_load_factor >= MIN_LOAD_FACTOR) {
    float curr_load_factor = _num_elements / _bucket_count;
    if (new_max_load_factor < curr_load_factor)
      rehash(_num_elements / new_max_load_factor);

    _max_load_factor = new_max_load_factor;
  }
};

template <typename T>
void utd::unordered_set_m<T>::insert_element(utd::base_node<T>* bucket,
                                             T&                 val) {
  node_m<T>* new_node = new node_m<T>(val);
  if (bucket->head == nullptr) {
    bucket->head = new_node;
    bucket->tail = new_node;

    new_node->prev = &_head;
    new_node->next = _head.next;

    if (_head.next) {
      _head.next->prev = new_node;
    }

    _head.next = new_node;
  } else {
    node_m<T>* prev_bucket_head = bucket->head;
    new_node->next              = prev_bucket_head;
    new_node->prev              = prev_bucket_head->prev;

    prev_bucket_head->prev->next = new_node;
    prev_bucket_head->prev       = new_node;

    bucket->head = new_node;
  }
}

template <typename T>
void utd::unordered_set_m<T>::rehash(size_t new_bucket_count) {
  base_node<T>* new_buckets = new base_node<T>[new_bucket_count];

  _head.next = nullptr;
  _head.prev = nullptr;
  for (int i = 0; i < _bucket_count; ++i) {
    node_m<T>* curr = _buckets[i].head;
    node_m<T>* tail = _buckets[i].tail;
    while (curr && curr != tail) {
      // TODO: to optimise
      const size_t hashed_index     = utd::hash<T>(curr->value);
      const size_t new_bucket_index = hashed_index % new_bucket_count;
      insert_element(&new_buckets[new_bucket_index], curr->value);
      curr = curr->next;
    }
    if (curr) {
      const size_t hashed_index     = utd::hash<T>(curr->value);
      const size_t new_bucket_index = hashed_index % new_bucket_count;
      insert_element(&new_buckets[new_bucket_index], curr->value);
    }
    _buckets[i].clear();
  }

  delete[] _buckets;
  _buckets      = new_buckets;
  _bucket_count = new_bucket_count;
};

template <typename T>
size_t
utd::unordered_set_m<T>::get_req_bucket_count(size_t num_of_elements) const {
  // TODO: remove use of std::ceil
  const float req_buckets_float = ceil(num_of_elements * _max_load_factor);
  return static_cast<size_t>(req_buckets_float);
};

template <typename T>
void utd::unordered_set_m<T>::insert(const T& v) {
  const size_t hashed_index = utd::hash<T>(v);
  const size_t bucket_index = hashed_index % _bucket_count;
  insert_element(_buckets[bucket_index], v);
  ++_num_elements;

  float new_load_factor = _num_elements / _bucket_count;
  if (new_load_factor > _max_load_factor) {
    size_t new_bucket_count =
      static_cast<size_t>(_num_elements / _max_load_factor);
    rehash(new_bucket_count);
  }
}

template <typename T>
void utd::unordered_set_m<T>::insert(T&& v) {
  const size_t hashed_index = utd::hash<T>(v);
  const size_t bucket_index = hashed_index % _bucket_count;
  insert_element(&_buckets[bucket_index], v);
  ++_num_elements;

  float new_load_factor = static_cast<float>(_num_elements) / _bucket_count;

  if (new_load_factor > _max_load_factor) {
    size_t new_bucket_count =
      static_cast<size_t>(_num_elements / _max_load_factor);
    rehash(new_bucket_count);
  }
}

template <typename T>
const utd::node_m<T>* utd::unordered_set_m<T>::begin() {
  return _head.next;
}
