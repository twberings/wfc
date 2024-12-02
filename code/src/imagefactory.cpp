
#include "image/imagefactory.hpp"
#include <fstream>
#include <optional>

;
#pragma pack(push, 1)
struct BitmapFileHeader {
  char header[2];
  int32_t file_size;
  int32_t reserved;
  int32_t data_offset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BitmapInfoHeader {
  int32_t header_size;
  int32_t width;
  int32_t height;
  int16_t planes;
  int16_t bits_per_pixel;
  int32_t compression;
  int32_t image_size;
  int32_t x_pixels_per_meter;
  int32_t y_pixels_per_meter;
  int32_t colors_used;
  int32_t important_colors;
};
#pragma pack(pop)

std::optional<Image> ImageFactory::load_bitmap(std::string path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return {};
  }

  BitmapFileHeader file_header;
  file.read(reinterpret_cast<char *>(&file_header), sizeof(BitmapFileHeader));
  if (file_header.header[0] != 'B' || file_header.header[1] != 'M') {
    return {};
  }

  BitmapInfoHeader info_header;
  file.read(reinterpret_cast<char *>(&info_header), sizeof(BitmapInfoHeader));
  if (info_header.bits_per_pixel != 24) {
    return {};
  }

  file.seekg(file_header.data_offset, file.beg);
  int row_size = ((info_header.width * 3 + 3) / 4) * 4;
  std::vector<char> row(row_size);

  size_t nr_pixels = info_header.width * info_header.height;
  std::vector<Pixel> pixels(nr_pixels);
  for (int i = 0; i < info_header.height; i++) {
    file.read(row.data(), row_size);
    for (int j = 0; j < info_header.width; j++) {
      uint8_t blue = row[j * 3];
      uint8_t green = row[j * 3 + 1];
      uint8_t red = row[j * 3 + 2];
      Pixel pixel(red, green, blue);
      pixels[(info_header.height - i - 1) * info_header.width + j] = pixel;
    }
  }
  return Image(info_header.width, info_header.height, pixels);
}

void ImageFactory::save_bitmap(std::string path, const Image &image) {
  std::ofstream file(path, std::ios::binary);
  BitmapFileHeader file_header;
  BitmapInfoHeader info_header;
  file_header.header[0] = 'B';
  file_header.header[1] = 'M';
  file_header.file_size = 0;
  file_header.reserved = 0;
  file_header.data_offset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
  info_header.header_size = sizeof(BitmapInfoHeader);
  info_header.width = image.Get_width();
  info_header.height = image.Get_height();
  info_header.planes = 1;
  info_header.bits_per_pixel = 24;
  info_header.compression = 0;
  info_header.image_size = 0;
  info_header.x_pixels_per_meter = 0;
  info_header.y_pixels_per_meter = 0;
  info_header.colors_used = 0;
  info_header.important_colors = 0;
  file.write(reinterpret_cast<char *>(&file_header), sizeof(BitmapFileHeader));
  file.write(reinterpret_cast<char *>(&info_header), sizeof(BitmapInfoHeader));

  int row_size = ((info_header.width * 3 + 3) / 4) * 4;
  std::vector<char> row(row_size, 0);
  for (int i = 0; i < image.Get_height(); i++) {
    for (int j = 0; j < image.Get_width(); j++) {
      Pixel pixel = image.Get_pixel(j, (image.Get_height() - i - 1));
      row[j * 3] = pixel.get_blue();
      row[j * 3 + 1] = pixel.get_green();
      row[j * 3 + 2] = pixel.get_red();
    }
    file.write(row.data(), row_size);
  }
}

Pixel ImageFactory::get_average_pixel(std::vector<Pixel> pixels) {
  int red = 0;
  int green = 0;
  int blue = 0;
  for (Pixel pixel : pixels) {
    red += pixel.get_red();
    green += pixel.get_green();
    blue += pixel.get_blue();
  }
  red /= pixels.size();
  green /= pixels.size();
  blue /= pixels.size();
  return Pixel(red, green, blue);
}

std::optional<Image>
ImageFactory::assemble_image(std::vector<std::vector<Image>> images, int rows,
                             int cols) {
  if (images.empty() || images[0].empty()) {
    return {};
  }
  int width = images[0][0].Get_width();
  int height = images[0][0].Get_height();

  std::vector<Pixel> pixels(width * rows * height * cols);

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      for (const Image &image : images[row * cols + col]) {
        if (image.Get_width() != width || image.Get_height() != height) {
          return {};
        }
      }
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          std::vector<Pixel> image_pixels;
          for (const Image &image : images[row * cols + col]) {
            image_pixels.push_back(image.Get_pixel(j, i));
          }
          pixels[(row * height + i) * width * cols + col * width + j] =
              get_average_pixel(image_pixels);
        }
      }
    }
  }
  return Image(width * cols, height * rows, pixels);
}
