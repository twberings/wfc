#include "image/imagetile.hpp"
#include "image/imagefactory.hpp"
#include "tilesets/circuit.hpp"

std::vector<std::shared_ptr<ITile<Image>>> circuit;

std::vector<ImageTile> circuit_tiles;

void populate_circuits(std::string path) {
    Image bridge =
      *ImageFactory::load_bitmap(path + "/bridge.bmp");
  Image component =
      *ImageFactory::load_bitmap(path + "/component.bmp");
  Image connection =
      *ImageFactory::load_bitmap(path + "/connection.bmp");
  Image corner =
      *ImageFactory::load_bitmap(path + "/corner.bmp");
  Image dskew =
      *ImageFactory::load_bitmap(path + "/dskew.bmp");
  Image skew =
      *ImageFactory::load_bitmap(path + "/skew.bmp");
  Image substrate =
      *ImageFactory::load_bitmap(path + "/substrate.bmp");
  Image tsplit =
      *ImageFactory::load_bitmap(path + "/tsplit.bmp");
  Image track =
      *ImageFactory::load_bitmap(path + "/track.bmp");
  Image transition =
      *ImageFactory::load_bitmap(path + "/transition.bmp");
  Image turn =
      *ImageFactory::load_bitmap(path + "/turn.bmp");
  Image viad =
      *ImageFactory::load_bitmap(path + "/viad.bmp");
  Image vias =
      *ImageFactory::load_bitmap(path + "/vias.bmp");
  Image wire =
      *ImageFactory::load_bitmap(path + "/wire.bmp");
  Socket s1(1, {1, 7, 8});
  Socket s2(2, {2});
  Socket s3(3, {3, 9});
  Socket s4(4, {5, 11});
  Socket s5(5, {4, 10});
  Socket s6(6, {6});
  Socket s7(7, {7, 1});
  Socket s8(8, {8, 1});
  Socket s9(9, {3});
  Socket s10(10, {5});
  Socket s11(11, {4});

  circuit_tiles.push_back(ImageTile(s1, s2, s1, s2, bridge));
  circuit_tiles.push_back(ImageTile(s3, s3, s3, s3, component));
  circuit_tiles.push_back(ImageTile(s1, s4, s9, s5, connection));
  circuit_tiles.push_back(ImageTile(s6, s6, s10, s11, corner));
  circuit_tiles.push_back(ImageTile(s7, s8, s7, s8, dskew));
  circuit_tiles.push_back(ImageTile(s7, s8, s6, s6, skew));
  circuit_tiles.push_back(ImageTile(s6, s6, s6, s6, substrate));
  circuit_tiles.push_back(ImageTile(s6, s1, s1, s1, tsplit));
  circuit_tiles.push_back(ImageTile(s1, s6, s1, s6, track));
  circuit_tiles.push_back(ImageTile(s2, s6, s1, s6, transition));
  /*circuit_tiles.push_back(ImageTile(s1, s1, s6, s6, turn));*/
  circuit_tiles.push_back(ImageTile(s6, s1, s6, s1, viad));
  circuit_tiles.push_back(ImageTile(s1, s6, s6, s6, vias));
  circuit_tiles.push_back(ImageTile(s6, s2, s6, s2, wire));

  for (auto const &tile : circuit_tiles) {
    auto rotations = tile.Get_rotations();
    circuit.insert(circuit.end(), rotations.begin(), rotations.end());
  }

}
