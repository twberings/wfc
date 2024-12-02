#pragma once

#include "image/image.hpp"
#include "wfc/itile.hpp"
#include <memory>
#include <vector>

extern std::vector<std::shared_ptr<ITile<Image>>> circuit;

void populate_circuits(std::string path);
