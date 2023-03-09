#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include "color.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  int max = dataset.MaxEle();
  int min = dataset.MinEle();
  int gray;
  std::vector<Color> temp;
  for (size_t i = 0; i < dataset.GetData().size(); i++) {
    for (size_t j = 0; j < dataset.GetData().at(i).size(); j++) {
      if (max != min) {
        gray = std::round(
            (static_cast<double>((dataset.GetData().at(i).at(j) - min)) /
             (static_cast<double>(max - min))) *
            static_cast<double>(255.0));
        Color shade_of_gray(gray, gray, gray);
        temp.push_back(shade_of_gray);
      } else {
        Color shade_of_gray(0, 0, 0);
        temp.push_back(shade_of_gray);
      }
    }
    image_.push_back(temp);
    temp.clear();
  }
  if (image_.size() != dataset.GetData().size()) {
    throw std::runtime_error("BAD");
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width,
                               size_t height) {
  ElevationDataset dataset(filename, width, height);
  GrayscaleImage img(dataset);
  image_ = img.image_;
  height_ = height;
  width_ = width;
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  const std::vector<std::vector<Color>>& ret = image_;
  return ret;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ToFile(name);
  ToFile << "P3";
  ToFile << "\n";
  ToFile << width_ << " " << height_;
  ToFile << "\n";
  ToFile << kMaxColorValue;
  ToFile << "\n";
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ToFile << image_.at(i).at(j).Red() << " " << image_.at(i).at(j).Green()
             << " " << image_.at(i).at(j).Blue();
      ToFile << " ";
    }
    ToFile << "\n";
  }
  ToFile << "\n";
}