#include "unicode/unicodeprinter.hpp"
std::string UnicodePrinter::Print() {
  std::string output;
  std::vector<std::vector<std::string>> characters = this->map.Output();
  for (size_t i = 0; i < characters.size(); i++) {
    if (characters[i].size() == 1) {
      output += characters[i][0];
    }
    if (characters[i].size() > 1) {
      /*output += std::to_string(characters[i].size());*/
      output += " ";
    }
    if ((i + 1) % row_length == 0) {
      output += "\n";
    }
  }
  return output;
}
