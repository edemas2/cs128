#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
#include <limits>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width,
                                   size_t height)
    : width_(width), height_(height) {
  const int kMax = -500000;
  const int kMin = 500000;
  max_ele_ = kMax;
  min_ele_ = kMin;

  std::ifstream ifs(filename);

  std::vector<std::vector<int>> temp(height_);
  std::vector<int> nums;
  unsigned long elements = 0;

  int num = 0;
  if (ifs.is_open()) {
    while (ifs.good()) {
      ifs >> num;
      if (ifs.fail()) {
        ifs.clear();
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
        elements++;
        nums.push_back(num);
        if (num > max_ele_) {
          max_ele_ = num;
        }
        if (num < min_ele_) {
          min_ele_ = num;
        }
        if (nums.size() == width_) {
          data_.push_back(nums);
          nums.clear();
        }
      }
    }
  } else {
    throw std::runtime_error("BAD");
  }

  if (elements != width_ * height_) {
    throw std::runtime_error("BAD");
  }
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  const std::vector<std::vector<int>>& ret = data_;
  return ret;
}