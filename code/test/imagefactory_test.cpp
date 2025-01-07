#include "image/imagefactory.hpp"
#include <gtest/gtest.h>
class ImageFactoryTest : public ::testing::Test {
protected:
  ImageFactoryTest() {}
  virtual ~ImageFactoryTest() {}
};

TEST_F(ImageFactoryTest, load_bitmap) {
  auto result = ImageFactory::load_bitmap("../assets/tilesets/test/t-up.bmp");
  ASSERT_TRUE(result);
  Image image = *result;
  EXPECT_EQ(image.Get_width(), 3);
  EXPECT_EQ(image.Get_height(), 3);
  EXPECT_EQ(image.Get_pixel(0, 2), Pixel(255, 255, 255));
  EXPECT_EQ(image.Get_pixel(1, 2), Pixel(255, 255, 255));
  EXPECT_EQ(image.Get_pixel(2, 2), Pixel(255, 255, 255));
  EXPECT_EQ(image.Get_pixel(0, 1), Pixel(0, 0, 0));
  EXPECT_EQ(image.Get_pixel(1, 1), Pixel(0, 0, 0));
  EXPECT_EQ(image.Get_pixel(2, 1), Pixel(0, 0, 0));
  EXPECT_EQ(image.Get_pixel(0, 0), Pixel(255, 255, 255));
  EXPECT_EQ(image.Get_pixel(1, 0), Pixel(0, 0, 0));
  EXPECT_EQ(image.Get_pixel(2, 0), Pixel(255, 255, 255));
}

TEST_F(ImageFactoryTest, save_bitmap) {
  /*std::remove("../assets/imgs/test-image-copy.bmp");*/
  /*auto result = ImageFactory::load_bitmap("../assets/imgs/test-image.bmp");*/
  /*ASSERT_TRUE(result);*/
  /*Image first_image = *result;*/
  /**/
  /*std::vector<std::vector<Image>> images(16, std::vector<Image>(1, first_image));*/
  /*result = ImageFactory::assemble_image(images, 4, 4);*/
  /*ImageFactory::save_bitmap("../assets/imgs/test-image-grid.bmp", *result);*/
  /*ImageFactory::save_bitmap("../assets/imgs/test-image-grid-rotated.bmp", *result);*/
  /**/
  /*ImageFactory::save_bitmap("../assets/imgs/test-image-copy.bmp", first_image);*/
  /*result = ImageFactory::load_bitmap("../assets/imgs/test-image-copy.bmp");*/
  /*ASSERT_TRUE(result);*/
  /*Image second_image = *result;*/
  /*ASSERT_EQ(first_image.Get_width(), second_image.Get_width());*/
  /*ASSERT_EQ(first_image.Get_height(), second_image.Get_height());*/
  /*for (int x = 0; x < first_image.Get_width(); x++) {*/
  /*  for (int y = 0; y < first_image.Get_height(); y++) {*/
  /*    EXPECT_EQ(first_image.Get_pixel(x, y), second_image.Get_pixel(x, y));*/
  /*  }*/
  /*}*/
  /**/
  /**/
}
