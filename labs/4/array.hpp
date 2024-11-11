#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

template <class T> class Array {
public:
  Array()
      : size_(0), capacity_(1), elements_(std::make_shared<T[]>(capacity_)) {}

  void add(T &element) {
    if (size_ >= capacity_) {
      resize(capacity_ * 2);
    }
    elements_[size_++] = element;
  }

  void removeAt(size_t index) {
    if (index >= size_)
      throw std::out_of_range("Index out of range");
    for (size_t i = index; i < size_ - 1; ++i) {
      elements_[i] = std::move(elements_[i + 1]);
    }
    --size_;
  }

  T &operator[](size_t index) const {
    if (index >= size_)
      throw std::out_of_range("Index out of range");
    return elements_[index];
  }

  double totalArea() const {
    double total = 0;
    for (size_t i = 0; i < size_; ++i) {
      total += static_cast<double>(elements_[i]);
    }
    return total;
  }

  size_t size() const { return size_; }

  void printAll() const {
    for (size_t i = 0; i < size_; ++i) {
      std::cout << "Figure " << i + 1 << ":\n";
      std::cout << "Center: " << elements_[i].center() << "\n";
      std::cout << "Vertices: " << elements_[i] << "\n";
      std::cout << "Area: " << static_cast<double>(elements_[i]) << "\n\n";
    }
  }

private:
  size_t size_;
  size_t capacity_;
  std::shared_ptr<T[]> elements_;

  void resize(size_t new_capacity) {
    std::shared_ptr<T[]> new_elements = std::make_shared<T[]>(new_capacity);
    for (size_t i = 0; i < size_; ++i) {
      new_elements[i] = std::move(elements_[i]);
    }
    elements_ = std::move(new_elements);
    capacity_ = new_capacity;
  }
};
