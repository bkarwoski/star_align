#pragma once
#include "deps/json.hpp"
#include <iostream>
#include <opencv2/imgcodecs.hpp>

std::string type2str(int type);

cv::Mat loadImage(std::string img_path, const nlohmann::json &options,
                  const int &flags = 1);

// todo image loader with json options?