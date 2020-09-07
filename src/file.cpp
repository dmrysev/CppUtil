#include "util/file.h"

#include <fstream>
#include <sstream>
#include <filesystem>


namespace Util {

std::vector<char> read_all_bytes(const std::string& filepath) {
    std::ifstream ifs(filepath, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(static_cast<size_t>(pos));

    ifs.seekg(0, std::ios::beg);
    ifs.read(result.data(), pos);

    return result;
}

std::string read_file(const std::string& filepath) {
    std::ifstream file(filepath);
    std::stringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();

    return content;
}

std::string filename(const std::string& path) {
    std::filesystem::path filepath(path);
    return filepath.filename().string();
}


std::string concat_files(const std::string& folder) {
    std::stringstream sstream;

    for(const auto& p: std::filesystem::directory_iterator(folder)) {
        std::ifstream fstream(p.path().string());
        sstream << fstream.rdbuf();
    }

    return sstream.str();
}

std::string absolute_path(const std::string& filepath)
{
    return std::filesystem::absolute({filepath}).string();
}

}
