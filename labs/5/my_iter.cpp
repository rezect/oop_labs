#pragma once

#include <iterator>

template <typename T> class MyIter {
private:
  T *ptr;

public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  MyIter(T *ptr = nullptr) : ptr(ptr) {}

  T &operator*() const { return *ptr; }

  T *operator->() const { return ptr; }

  MyIter &operator++() {
    ++ptr;
    return *this;
  }

  MyIter operator++(int) {
    MyIter tmp = *this;
    ++(*this);
    return tmp;
  }

  bool operator==(const MyIter &other) const { return ptr == other.ptr; }

  bool operator!=(const MyIter &other) const { return ptr != other.ptr; }
};
