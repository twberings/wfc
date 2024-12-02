#pragma once

#include "image/image.hpp"
#include "wfc/tile2d.hpp"
class ImageTile : public Tile2d<Image> {
public:
  ImageTile(Socket up, Socket right, Socket down, Socket left, Image image)
      : Tile2d(up, right, down, left), image(image) {}
  Image Output() override { return image; }
  virtual bool Check_constraints(std::shared_ptr<ITile<Image>> &other_tile,
                                 int direction) override;
  std::vector<std::shared_ptr<ImageTile>> Get_rotations() const;

private:
  Image image;
  bool check_image(Image &other);
};
