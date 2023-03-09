#include "path.hpp"

#include <iostream>

Path::Path(size_t length, size_t starting_row)
    : length_(length), starting_row_(starting_row) {
  std::vector<size_t> x(length);
  path_ = x;
}

void Path::IncEleChange(unsigned int value) {
  if (value > 0) {
    ele_change_ += value;
  }
}

void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }