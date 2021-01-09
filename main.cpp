#include "deps/json.hpp"
#include "util.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video/tracking.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cout << "Usage: ./main </path/to/images>" << std::endl;
    exit(1);
  }
  std::ifstream ifs("../options.json");
  json options = json::parse(ifs);

  std::string path = argv[1];
  std::vector<std::string> sorted_filenames;
  for (auto &entry : std::filesystem::directory_iterator(path)) {
    sorted_filenames.push_back(entry.path().string());
  }
  std::sort(sorted_filenames.begin(), sorted_filenames.end());

  if (options["image_count"] > 1) {
    auto first = sorted_filenames.begin();
    auto last = sorted_filenames.begin() + options["image_count"] + 1;
    sorted_filenames = std::vector<std::string>(first, last);
  }

  cv::Mat template_img =
      loadImage(*sorted_filenames.begin(), options, cv::IMREAD_GRAYSCALE);
  cv::Mat template_img_color = loadImage(*sorted_filenames.begin(), options);
  cv::Mat img_accumulated;
  template_img_color.clone().convertTo(img_accumulated, CV_32S);
  sorted_filenames.erase(sorted_filenames.begin());
  cv::imwrite("../loaded.jpg", template_img_color);

  cv::Mat transform = cv::Mat::eye(3, 3, CV_32FC1);
  std::map<std::string, cv::Mat> transforms;

  for (const auto &img_path : sorted_filenames) {
    cv::Mat image = loadImage(img_path, options, cv::IMREAD_GRAYSCALE);
    double retval = cv::findTransformECC(template_img, image, transform,
                                         cv::MOTION_HOMOGRAPHY);
    transforms[img_path] = transform.clone();
    std::cout << "ECC: " << retval << std::endl;
  }

  for (const auto &img_path : sorted_filenames) {
    cv::Mat image = loadImage(img_path, options);
    cv::Mat image_warped;
    cv::warpPerspective(image, image_warped, transforms[img_path], image.size(),
                        cv::WARP_INVERSE_MAP);
    cv::add(img_accumulated, image_warped, img_accumulated, cv::noArray(),
            CV_32S);
  }
  img_accumulated /= ((sorted_filenames.size() + 1) /
                      static_cast<double>(options["normalization_multiplier"]));
  cv::imwrite("../normalized.jpg", img_accumulated);
  return 0;
}
