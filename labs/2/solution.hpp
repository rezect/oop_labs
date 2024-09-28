#include "string"
#include <vector>

using u_char = unsigned char;

class Seven {
public:
  Seven();
  Seven(const size_t& n, u_char t = '0');
  Seven(const std::initializer_list<u_char> &t);
  Seven(const std::string &t);

  Seven(const Seven& other);
  Seven(Seven&& other) noexcept;

  Seven operator+(const Seven& other);
  Seven operator-(const Seven& other);
  Seven& operator=(const Seven& other);
  Seven& operator=(Seven&& other);

  Seven& operator+=(const Seven& other);
  Seven& operator-=(const Seven& other);

  bool operator>(const Seven& other) const;
  bool operator<(const Seven& other) const;
  bool operator==(const Seven& other) const;

  u_char& operator[](size_t ind);

  std::string str_view() const;
  size_t size() const;

  virtual ~Seven() noexcept;

private:
  u_char* nums;
  size_t sz;
};