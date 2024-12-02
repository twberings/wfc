#include "image/image.hpp"
#include "image/imageprinter.hpp"
#include "wfc/map2d.hpp"
#include "tilesets/circuit.hpp"

#define WIDTH 20
#define HEIGHT 20


int main() {
  populate_circuits("../assets/tilesets/circuit");
  Map2D<Image> map(WIDTH, HEIGHT, circuit);
  ImagePrinter printer(map, HEIGHT, WIDTH);
  /*WaveFunctionCollapse<Image> wfc(&map, &printer, time(NULL));*/
  /*Image image = wfc.Solve();*/
  Image image;
  srand(time(NULL));
  while (!map.Is_solved()) {
    map.Collapse_at(map.Lowest_entropy());
    image = printer.Print();
    ImageFactory::save_bitmap("../assets/imgs/output/circuit.bmp", image);
  }
}
