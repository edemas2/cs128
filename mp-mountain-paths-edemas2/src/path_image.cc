#include "path_image.hpp"

#include <fstream>
#include <iostream>

#include "color.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  path_image_ = image.GetImage();
  width_ = image.Width();
  height_ = image.Height();
  size_t bestElv = 7000000;
  size_t bestLocation = 0;
  Path best(1, 1);
  for (size_t i = 0; i < height_; i++) {
    Path p = CreatePath(dataset, i);

    paths_.push_back(p);
    if (paths_.at(i).EleChange() < bestElv) {
      bestElv = paths_.at(i).EleChange();
      bestLocation = i;
      best = paths_.at(i);
    }
  }

  for (size_t i = 0; i < paths_.at(bestLocation).GetPath().size(); i++) {
    std::cout << paths_.at(bestLocation).GetPath().at(i) << std::endl;
  }

  for (size_t i = 0; i < best.GetPath().size(); i++) {
    Color g(31, 253, 13);
    path_image_.at(best.GetPath().at(i)).at(i) = g;
  }
  for (size_t i = 0; i < paths_.at(i).GetPath().size(); i++) {
    if (i != bestLocation) {
      Color r(252, 25, 63);
      path_image_.at(paths_.at(i).GetPath().at(i)).at(i) = r;
    }
  }
  // for (size_t i = 0; i < paths_.size(); i++) {
  //   // for (size_t j = 0; j < paths_.at(i).GetPath().size(); j++) {
  //   //   if (i != bestLocation) {
  //   //     Color r(252, 25, 63);
  //   //     path_image_.at(paths_.at(i).GetPath().at(i))
  //   //         .at(paths_.at(i).GetPath().at(j)) = r;
  //   //   }
  //   // }
  // }
}

Path PathImage::CreatePath(const ElevationDataset& dataset, size_t start) {
  width_ = dataset.Width();
  Path toReturn(width_, start);
  toReturn.SetLoc(0, start);
  size_t height = start;
  int startValue = dataset.GetData().at(start).at(0);
  int previous = startValue;

  for (size_t i = 0; i < width_ - 1; i++) {
    int up = 0;
    int same = 0;
    int down = 0;
    if (height != dataset.Height() - 1) {
      up = abs(previous - dataset.GetData().at(height + 1).at(i + 1));
    } else {
      up = 50000;
    }
    same = abs(previous - dataset.GetData().at(height).at(i + 1));
    if (height != 0) {
      down = abs(previous - dataset.GetData().at(height - 1).at(i + 1));
    } else {
      down = 50000;
    }
    int smallest = SmallestValue(same, down, up);
    toReturn.IncEleChange(smallest);
    if (smallest == same) {
      previous = dataset.GetData().at(height).at(i + 1);
    } else if (smallest == up) {
      previous = dataset.GetData().at(height + 1).at(i + 1);
      height = height + 1;
    } else if (smallest == down) {
      previous = dataset.GetData().at(height - 1).at(i + 1);
      height = height - 1;
    }
    toReturn.SetLoc(i + 1, height);
  }
  return toReturn;
}

int PathImage::SmallestValue(int x, int y, int z) {
  int smallest;
  if (x < y) {
    smallest = x;
  } else {
    smallest = y;
  }
  if (z < smallest) {
    smallest = z;
  }
  if (x == y || x == z) {
    smallest = x;
  }
  return smallest;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ToFile(name);
  ToFile << "P3";
  ToFile << "\n";
  ToFile << width_ << " " << height_;
  ToFile << "\n";
  ToFile << kMaxColorValue;
  ToFile << "\n";
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ToFile << path_image_.at(i).at(j).Red() << " "
             << path_image_.at(i).at(j).Green() << " "
             << path_image_.at(i).at(j).Blue();
      ToFile << " ";
    }
    ToFile << "\n";
  }
  ToFile << "\n";
}