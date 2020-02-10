#pragma once

#include <vector>
#include <string>

namespace ABB::OptiMold::Utils {

std::vector<char> read_all_bytes(const std::string& filepath);

std::string read_file(const std::string& filepath);

std::string filename(const std::string& path);

}
