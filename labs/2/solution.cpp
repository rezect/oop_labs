#include "solution.hpp"
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

Seven::Seven() : nums(nullptr), sz(0) {}

Seven::Seven(const size_t& n, u_char t) {
  nums = new u_char[10];
  for (int i = 0; i < n; ++i) {
    nums[i] = t;
  }
  sz = n;
}

Seven::Seven(const std::initializer_list<u_char>& t) {
  nums = new u_char[t.size()];
  sz = 0;
  size_t i = 0;
  for (const u_char num : t) {
    nums[i] = num;
    ++i;
    ++sz;
  }
}

Seven::Seven(const std::string& t) {
  nums = new u_char[t.size()];
  for (size_t i = 0; i < t.size(); ++i) {
    // if (t[i] > '6' || t[i] < '0') {
    //   throw std::invalid_argument("Неверная цифра для семиричной системы");
    // }
    nums[t.size() - i - 1] = t[i];
  }
  sz = t.size();
}

Seven::Seven(const Seven& other) {
  nums = new u_char[other.sz];
  sz = other.sz;
  std::memcpy(nums, other.nums, other.sz * sizeof(u_char));
}

Seven::Seven(Seven&& other) noexcept {
  nums = other.nums;
  sz = other.sz;
  other.nums = nullptr;
  other.sz = 0;
}

Seven Seven::operator+(const Seven& other) {
  if (other.sz == 0) {return Seven(*this);}
  if (sz == 0) {return Seven(other);}

  std::string ans;
  int carry = 0;
  int sum = 0;

  int max_sz = std::max(sz, other.sz);
  int min_sz = std::min(sz, other.sz);

  for (size_t i = 0; i < min_sz; ++i) {
    sum = nums[i] + other.nums[i] + carry - '0' - '0';
    if (sum >= 7) {
      carry = 1;
      ans.push_back(sum - 7 + '0');
    } else {
      carry = 0;
      ans.push_back(sum + '0');
    }
  }

  if (sz == max_sz) {
    for (size_t i = min_sz; i < max_sz; ++i) {
      if (nums[i] + carry == '7') {
        carry = 1;
        ans.push_back('0');
        continue;
      }
      ans.push_back(nums[i] + carry);
      carry = 0;
    }
  } else {
    for (size_t i = min_sz; i < max_sz; ++i) {
      if (other.nums[i] + carry == '7') {
        carry = 1;
        ans.push_back('0');
        continue;
      }
      ans.push_back(other.nums[i] + carry);
      carry = 0;
    }
  }

  if (carry) {
    ans.push_back('1');
  }

  reverse(ans.begin(), ans.end());

  return Seven(ans);
}

Seven Seven::operator-(const Seven& other) {
  if (*this < other) {
    throw std::invalid_argument("Первый аргумент меньше второго в вычитании");
  }
  if (other.sz == 0) {return Seven(*this);}
  if (sz == 0) {return Seven(other);}

  std::string ans;
  int carry = 0;
  int diff = 0;

  int max_sz = sz;
  int min_sz = other.sz;

  for (size_t i = 0; i < min_sz; ++i) {
    diff = (nums[i] - '0') - (other.nums[i] - '0') - carry;
    if (diff < 0) {
      carry = 1;
      ans.push_back(7 + diff + '0');
    } else {
      carry = 0;
      ans.push_back(diff + '0');
    }
  }

  for (size_t i = min_sz; i < max_sz; ++i) {
    if (nums[i] - carry != '0') {
      ans.push_back(nums[i] - carry);
    }
    carry = 0;
  }

  for (size_t i = 0; i < ans.size() + 1; ++i) {
    if (ans[ans.size() - 1] != '0') {
      break;
    }
    ans.pop_back();
  }

  reverse(ans.begin(), ans.end());

  return Seven(ans);
}

Seven& Seven::operator=(const Seven& other) {
  if (this == &other) {
    return *this;
  }

  delete[] nums;
  sz = other.sz;
  nums = new u_char[sz];
  std::memcpy(nums, other.nums, other.sz * sizeof(u_char));

  return *this;
}

Seven& Seven::operator=(Seven&& other) {
  if (this == &other) {
    return *this;
  }

  delete[] nums;
  sz = other.sz;
  nums = other.nums;
  other.nums = nullptr;
  other.sz = 0;

  return *this;
}

Seven& Seven::operator+=(const Seven& other) {
  *this = std::move(*this + other);
  return *this;
}

Seven& Seven::operator-=(const Seven& other) {
  *this = std::move(*this - other);
  return *this;
}

bool Seven::operator>(const Seven& other) const {
  if (sz != other.sz) {
    return sz > other.sz;
  }
  for (size_t i = 0; i < sz; ++i) {
    for (int i = sz - 1; i >= 0; --i) {
      if (nums[i] != other.nums[i])
        return nums[i] > other.nums[i];
    }
  }
  return false;
}

bool Seven::operator<(const Seven& other) const {
  return other > *this;
}

bool Seven::operator==(const Seven& other) const {
  if (sz != other.sz)
    return false;
  return !std::memcmp(nums, other.nums, sz * sizeof(u_char));
}

u_char& Seven::operator[](size_t ind) {
  return nums[ind];
}

std::string Seven::str_view() const {
  std::string ans;
  for (size_t i = 0; i < sz; ++i) {
    ans.push_back(nums[sz - i - 1]);
  }
  return ans;
}

size_t Seven::size() const {
  return sz;
}

Seven::~Seven() noexcept {
  delete[] nums;
  nums = nullptr;
  sz = 0;
}

// int main() {
//   Seven m("1000");
//   Seven n("1000");
//   Seven diff = m - n;
//   std::cout << diff.str_view() << std::endl;
// }