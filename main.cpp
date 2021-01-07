#include "deps/json.hpp"
#include "util.h"
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
using json = nlohmann::json;

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cout << "Usage: ./main </path/to/images>" << std::endl;
    exit(1);
  }
  std::ifstream ifs("../options.json");
  json options = json::parse(ifs);

  std::string path = argv[1];
  std::set<std::string> sorted_filenames;
  for (auto &entry : fs::directory_iterator(path)) {
    sorted_filenames.insert(entry.path().string());
  }

  cv::Mat template_img =
      cv::imread(*sorted_filenames.begin(), cv::IMREAD_GRAYSCALE);
  if (options["crop"]) {
    template_img =
        template_img(cv::Rect(options["crop_x"], options["crop_y"],
                              options["crop_width"], options["crop_height"]));
  }

  cv::imwrite("../cropped.jpg", template_img);
  sorted_filenames.erase(sorted_filenames.begin());

  cv::Mat transform = cv::Mat::eye(3, 3, CV_32FC1);

  for (const auto &img_path : sorted_filenames) {
    cv::Mat image = cv::imread(img_path, cv::IMREAD_GRAYSCALE);
    if (options["crop"]) {
      image = image(cv::Rect(options["crop_x"], options["crop_y"],
                             options["crop_width"], options["crop_height"]));
    }
    double retval = cv::findTransformECC(template_img, image, transform,
                                         cv::MOTION_HOMOGRAPHY);
    std::cout << "retval: " << retval << std::endl;
    std::cout << transform << std::endl;
  }

  if (!cv::imwrite("./output.jpg", template_img)) {
    std::cerr << "could not write image" << std::endl;
  }

  return 0;
}
// /home/blake/Pictures/Sand_Dune_Stars/time_lapse/jpg/DSC07974.JPG
