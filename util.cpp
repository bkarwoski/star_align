#include "util.h"

std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch (depth) {
  case CV_8U:
    r = "8U";
    break;
  case CV_8S:
    r = "8S";
    break;
  case CV_16U:
    r = "16U";
    break;
  case CV_16S:
    r = "16S";
    break;
  case CV_32S:
    r = "32S";
    break;
  case CV_32F:
    r = "32F";
    break;
  case CV_64F:
    r = "64F";
    break;
  default:
    r = "User";
    break;
  }

  r += "C";
  r += (chans + '0');

  return r;
}

cv::Mat loadImage(std::string img_path, const nlohmann::json &options,
                  const int &flags) {
  cv::Mat image = cv::imread(img_path, flags);
  if (!image.data) {
    std::cerr << "could not open the image file" << img_path << std::endl;
    return image;
  }
  if (options["crop"]) {
    image = image(cv::Rect(options["crop_x"], options["crop_y"],
                           options["crop_width"], options["crop_height"]));
  }
  return image;
}