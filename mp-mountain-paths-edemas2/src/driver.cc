#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
int main() {
  ElevationDataset elevationtest(
      "./example-data/ex_input_data/exampleFromDOC.dat", 6, 5);
  GrayscaleImage grayscale("./example-data/ex_input_data/exampleFromDOC.dat", 6,
                           5);
  grayscale.ToPpm("./example-data/ex_input_data/testPPM.dat");
  PathImage pimg(grayscale, elevationtest);
}
