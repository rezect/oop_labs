#include "my_iter.cpp"
#include <iostream>
#include <iterator>
#include <vector>

struct BlockInfo {
  friend class CustomMemoryResourse;
  bool is_free;
  void *address;
  size_t size;

  BlockInfo(bool __is_free, void *__address, size_t __size)
      : is_free(__is_free), address(__address), size(__size) {}
};

class CustomMemoryResourse : public std::pmr::memory_resource {
private:
  std::vector<BlockInfo> blocks;
  void *memory;
  size_t total_size;

protected:
  void *do_allocate(size_t __bytes, size_t __alignment = 0) override {
    for (auto &block : blocks) {
      if (block.is_free && block.size >= __bytes) {
        void *aligned_address = static_cast<void *>(block.address);
        block.is_free = false;
        blocks.push_back(
            BlockInfo(true, shift_pointer(aligned_address, __bytes), block.size - __bytes));
        
        return aligned_address;
      }
    }
    throw std::bad_alloc();
  }

  void do_deallocate(void *__p, size_t __bytes, size_t __alignment = 0) override {
    for (auto &block : blocks) {
      if (block.address == __p) {
        block.is_free = true;
        break;
      }
    }
  }

  bool do_is_equal(const memory_resource &__other) const noexcept override {
    return *this == __other;
  }

public:
  CustomMemoryResourse(size_t __bytes)
      : memory(::operator new(__bytes)), total_size(__bytes),
        blocks() {
    blocks.push_back(BlockInfo(true, memory, __bytes));
  }

  ~CustomMemoryResourse() { ::operator delete(memory); }

private:
  void* shift_pointer(void* ptr, std::ptrdiff_t bytes) {
    return static_cast<void*>(static_cast<char*>(ptr) + bytes);
  }
};

template <typename T> class MyStack {
private:
  std::pmr::vector<T> data;

public:
  using allocator_type = std::pmr::polymorphic_allocator<T>;

  MyStack(const allocator_type &alloc = {}) : data(alloc) {}

  void push(const T &value) { data.push_back(value); }

  void pop() {
    if (data.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    data.pop_back();
  }

  T &top() {
    if (data.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return data.back();
  }

  bool empty() const { return data.empty(); }

  std::size_t size() const { return data.size(); }
};
