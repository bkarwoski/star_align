#include <assert.h>
#include <ceres/ceres.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video/tracking.hpp>
#include <set>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: ./main </path/to/images>" << std::endl;
    exit(1);
  }
  std::string path = argv[1];
  std::set<std::string> sorted_filenames;
  // cv::findTransformECC
  for (auto &entry : fs::directory_iterator(path)) {
    sorted_filenames.insert(entry.path().string());
  }

  cv::Mat template_img = cv::imread(*sorted_filenames.begin());
  sorted_filenames.erase(sorted_filenames.begin());

  for (const auto &img_path : sorted_filenames) {
    std::cout << img_path << std::endl;
  }

  if (!cv::imwrite("./output.jpg", template_img)) {
    std::cerr << "could not write image" << std::endl;
  }

  return 0;
}
// /home/blake/Pictures/Sand_Dune_Stars/time_lapse/jpg/DSC07974.JPG
