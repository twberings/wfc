#include "image/imagetile.hpp"
bool ImageTile::Check_constraints(std::shared_ptr<ITile<Image>> &other_tile,
                                  int direction) {
  std::shared_ptr<ImageTile> other_image_tile =
      std::dynamic_pointer_cast<ImageTile>(other_tile);
  if (!other_image_tile) {
    return false;
  }
  return (Tile2d<Image>::Check_constraints(other_tile, direction) &&
          image.width == other_image_tile->image.width &&
          image.height == other_image_tile->image.height);
}

std::vector<std::shared_ptr<ImageTile>> ImageTile::Get_rotations() const {
  std::vector<std::shared_ptr<ImageTile>> rotations;
  rotations.push_back(std::make_shared<ImageTile>(
      sockets[2], sockets[1], sockets[3], sockets[0], image));
  rotations.push_back(std::make_shared<ImageTile>(
      sockets[0], sockets[2], sockets[1], sockets[3], image.Get_rotated()));
  rotations.push_back(std::make_shared<ImageTile>(
      sockets[3], sockets[0], sockets[2], sockets[1],
      image.Get_rotated().Get_rotated()));
  rotations.push_back(std::make_shared<ImageTile>(
      sockets[1], sockets[3], sockets[0], sockets[2],
      image.Get_rotated().Get_rotated().Get_rotated()));
  return rotations;
}
