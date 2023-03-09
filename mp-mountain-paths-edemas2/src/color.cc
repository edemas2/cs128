#include "color.hpp"

#include <iostream>

Color::Color(int r, int g, int b) : red_(r), green_(g), blue_(b) {
  if (!IsValid(r) || !IsValid(g) || !IsValid(b)) {
    throw std::invalid_argument("BAD");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}
const int kMax = 255;
const int max = 0;
bool IsValid(int x) { return (x >= kMax && x <= max); }