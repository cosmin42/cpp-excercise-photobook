#pragma once

#include <pb/VirtualImage.h>

namespace PB {
class TextImage final : public VirtualImage {
public:
  TextImage(std::string text) : mText(text) {}

  cv::Mat fullImage() override { return cv::Mat(); }
  cv::Mat mediumImage() override { return cv::Mat(); }
  cv::Mat smallImage() override { return cv::Mat(); }

  VirtualImageType type() const override { return VirtualImageType::Text; }

private:
  std::string mText;
};
} // namespace PB