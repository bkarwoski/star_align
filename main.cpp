#include <assert.h>
#include <ceres/ceres.h>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/tracking.hpp>
#include <string>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: ./main </path/to/images>" << std::endl;
    exit(1);
  }
  std::string path = argv[1];
  cv::Mat img = cv::imread(path);
  if (!cv::imwrite("./output.jpg", img)) {
    std::cerr << "could not write image" << std::endl;
  }

  std::cout << "hello world" << std::endl;
  return 0;
}
// /home/blake/Pictures/Sand_Dune_Stars/time_lapse/jpg/DSC07974.JPG
