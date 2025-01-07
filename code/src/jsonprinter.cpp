#include "json/jsonprinter.hpp"

std::string JsonTilePrinter::Print() {
  auto output = map.Output();
  std::vector<std::string> row_strings;
  for (int i = 0; i < rows; i++) {
    std::vector<std::vector<std::string>> row(output.begin() + i * cols,
                                              output.begin() + (i + 1) * cols);
    std::vector<std::string> tile_strings;
    for (auto &tile : row) {
      tile_strings.push_back(VectorToString(tile, true));
    }
    row_strings.push_back(VectorToString(tile_strings));
  }
  return VectorToString(row_strings);
}

std::string JsonTilePrinter::VectorToString(std::vector<std::string> &vec,
                                            bool with_quotes) {
  std::string str = "[";
  for (auto &s : vec) {
    if (with_quotes) {
      str += "\"" + s + "\",";
    } else {
      str += s + ",";
    }
  }
  str.pop_back();
  str += "]";
  return str;
}
