#include "../utils/hash.h"
#include <cmath>    // TODO: remove this
#include <iostream> // Remove after testing

constexpr size_t DEFAULT_BUCKET_COUNT{ 1 };
constexpr int    EXPAND_SIZE_MULTIPLIER{ 2 };
constexpr float  DEFAULT_MAX_LOAD_FACTOR{ 1.0 };

template <typename T>
utd::node<T>::node(const T& val) : value(val), next(nullptr) {}

template <typename T>
utd::node<T>::node(T&& val) : value(val), next(nullptr) {}

template <typename T>
utd::linked_list<T>::linked_list() : head(nullptr) {}

template <typename T>
void utd::linked_list<T>::clear() {
  node_ptr curr_ptr = head;
  while (curr_ptr) {
    node_ptr next = curr_ptr->next;
    delete curr_ptr;
    curr_ptr = next;
  }
}

template <typename T>
utd::unordered_set<T>::unordered_set()
    : _num_elements(0)
    , _bucket_count(DEFAULT_BUCKET_COUNT)
    , _max_load_factor(DEFAULT_MAX_LOAD_FACTOR) {
  _buckets = new linked_list<T>[DEFAULT_BUCKET_COUNT]();
}

template <typename T>
utd::unordered_set<T>::unordered_set(const unordered_set& s)
    : _num_elements(s._num_elements)
    , _bucket_count(s._bucket_count)
    , _max_load_factor(s._max_load_factor) {
  copyBuckets(s);
}

template <typename T>
utd::unordered_set<T>::unordered_set(unordered_set&& s)
    : _num_elements(s._num_elements)
    , _bucket_count(s._bucket_count)
    , _buckets(s._buckets)
    , _max_load_factor(s._max_load_factor) {
  s._num_elements    = 0;
  s._bucket_count    = 0;
  s._buckets         = nullptr;
  s._max_load_factor = 0;
}

template <typename T>
utd::unordered_set<T>&
utd::unordered_set<T>::operator=(const unordered_set& s) {
  _num_elements    = s._num_elements;
  _bucket_count    = s._bucket_count;
  _max_load_factor = s._max_load_factor;

  delete[] _buckets;
  copyBuckets(s);
  return *this;
}

template <typename T>
utd::unordered_set<T>& utd::unordered_set<T>::operator=(unordered_set&& s) {
  _num_elements    = s._num_elements;
  _bucket_count    = s._bucket_count;
  _buckets         = s._buckets;
  _max_load_factor = s._max_load_factor;

  s._num_elements    = 0;
  s._bucket_count    = 0;
  s._buckets         = nullptr;
  s._max_load_factor = 0;
}

template <typename T>
utd::unordered_set<T>::~unordered_set() {
  for (int i = 0; i < _bucket_count; i++)
    _buckets[i].clear();
  delete[] _buckets;
}

// TODO: this can be a util method
template <typename T>
size_t utd::unordered_set<T>::getRequiredBucketCount(size_t size) const {
  // TODO: remove use of std::ceil
  const float req_buckets_float = ceil(size * _max_load_factor);
  return static_cast<size_t>(req_buckets_float);
}

template <typename T>
void utd::unordered_set<T>::insertElement(node_ptr& bucket_node_ref,
                                          const T&  item) {
  bucket_node_ref = new node<T>(item);
  _num_elements++;

  // check if rehash is needed
  const size_t req_buckets = getRequiredBucketCount(_num_elements);
  if (req_buckets > _bucket_count)
    // TODO: more efficient size increase?
    changeBucketCount(_bucket_count * EXPAND_SIZE_MULTIPLIER);
}

template <typename T>
void utd::unordered_set<T>::insertElement(node_ptr& bucket_node_ref, T&& item) {
  bucket_node_ref = new node<T>(item);
  _num_elements++;

  // check if rehash is needed
  const size_t req_buckets = getRequiredBucketCount(_num_elements);
  if (req_buckets > _bucket_count)
    // TODO: more efficient size increase?
    changeBucketCount(_bucket_count * EXPAND_SIZE_MULTIPLIER);
}

template <typename T>
void utd::unordered_set<T>::changeBucketCount(size_t new_bucket_count) {
  linked_list<T>* new_buckets = new linked_list<T>[new_bucket_count]();

  // moving data from old buckets to new buckets, can't use memcpy because
  // rehashing is needed
  for (int i = 0; i < _bucket_count; i++) {
    node_ptr curr_ptr = _buckets[i].head;

    // iterate over every node in old bucket
    while (curr_ptr) {
      const size_t hashed_index     = utd::hash<T>(curr_ptr->value);
      const size_t new_bucket_index = hashed_index % new_bucket_count;

      // get last pointer address of new bucket
      node_ptr* last_ptr_addr = &(new_buckets[new_bucket_index].head);
      while (*last_ptr_addr)
        last_ptr_addr = &((*last_ptr_addr)->next);

      // point last pointer of new bucket to existing node in old bucket
      *last_ptr_addr = curr_ptr;

      // iterate to next node in old bucket
      curr_ptr = curr_ptr->next;

      // last node in new bucket should not point to anything
      (*last_ptr_addr)->next = nullptr;
    }
  }

  delete[] _buckets;
  _buckets      = new_buckets;
  _bucket_count = new_bucket_count;
}

template <typename T>
void utd::unordered_set<T>::copyBuckets(const utd::unordered_set<T>& s) {
  _buckets = new linked_list<T>[s._bucket_count];

  for (int i = 0; i < s._bucket_count; i++) {
    node_ptr* target = &(_buckets[i].head);
    node_ptr  src    = s._buckets[i].head;
    while (src) {
      *target = new node<T>(src->value);
      target  = &((*target)->next);
      src     = src->next;
    }
  }
}

template <typename T>
size_t utd::unordered_set<T>::size() const noexcept {
  return _num_elements;
}

template <typename T>
size_t utd::unordered_set<T>::bucket_count() const noexcept {
  return _bucket_count;
}

template <typename T>
float utd::unordered_set<T>::max_load_factor() const noexcept {
  return _max_load_factor;
}

template <typename T>
void utd::unordered_set<T>::max_load_factor(float load_factor) {
  _max_load_factor = load_factor;
}

template <typename T>
void utd::unordered_set<T>::reserve(size_t size) {
  const size_t req_buckets = getRequiredBucketCount(size);
  if (req_buckets > _bucket_count)
    changeBucketCount(req_buckets);
}

// TODO: should return pair<iterator,bool>
template <typename T>
void utd::unordered_set<T>::insert(const T& item) {
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

// TODO: should return pair<iterator,bool>
template <typename T>
void utd::unordered_set<T>::insert(T&& item) {
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
}

template <typename T>
void utd::unordered_set<T>::print_buckets() {
  std::cout << '[';
  for (int i = 0; i < _bucket_count; i++) {
    node_ptr curr = _buckets[i].head;
    while (curr) {
      std::cout << curr->value << ',';
      curr = curr->next;
    }
  }
  std::cout << ']' << '\n';
}