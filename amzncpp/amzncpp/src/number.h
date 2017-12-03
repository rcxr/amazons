#pragma once
#include <string>

class Number {
public:
  Number(int n, int d);
  Number();
  int const n;
  int const d;
  bool const valid;
  Number operator+(Number const& other) const;
  std::string toString() const;
private:
  Number(int n, int d, bool validNumber);
};

inline Number::Number(int n, int d, bool validNumber) : n(n), d(d), valid(validNumber) {}
inline Number::Number(int n, int d) : Number(n, d, true) {}
inline Number::Number() : Number(0, 0, false) {}

inline Number Number::operator+(Number const& other) const {
  if (!valid || !other.valid) {
    return Number();
  }
  int n = this->n;
  int d = this->d;
  while (d < other.d) {
    n <<= 1;
    d <<= 1;
  }
  while (other.d < d) {
    n >>= 1;
    d >>= 1;
  }
  return Number(n + other.n, d);
}

inline std::string Number::toString() const {
  return valid ? std::to_string(n) + "/" + std::to_string(d) : "?";
}
