#include <gtest/gtest.h>

#include <pb/CollageLibraryAssistant.h>

using namespace PB;

TEST(TestCollageAssistant, ExtractProfile)
{
  CollageLibraryAssistant assistant(std::filesystem::current_path(),
                                    std::filesystem::current_path());

  auto paths = assistant.createNumberedImages({2480, 1754});

  EXPECT_EQ(paths.size(), 10);

  AspectRatio aspectRatio = {4, 3};

  auto templatePath = std::filesystem::current_path() / Path("svg-templates") /
                      "2x1-simple.svg.template";

  assistant.createTemplateThumbnail(templatePath, aspectRatio, {2480, 1754});

  for (auto i = 0; i < 10; ++i) {
    std::filesystem::remove(std::filesystem::current_path() /
                            (std::string("placeolder_") + std::to_string(i)));
  }

  std::filesystem::remove(std::filesystem::current_path() /
                          "template_4to3-2480x1754.svg");
}