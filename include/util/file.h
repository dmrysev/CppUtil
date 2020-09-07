#pragma once

#include <vector>
#include <string>

namespace Util {

std::vector<char> read_all_bytes(const std::string& filepath);
std::string read_file(const std::string& filepath);
std::string filename(const std::string& path);
std::string concat_files(const std::string& folder);
std::string absolute_path(const std::string& filepath);

}
