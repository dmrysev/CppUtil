#include "file.h"

#include <fstream>
#include <sstream>
#include <experimental/filesystem>

using std::vector;
using std::ifstream;
using std::ios;
using std::string;


namespace ABB::OptiMold::Utils {

vector<char> read_all_bytes(const std::string& filepath) {
    ifstream ifs(filepath, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();
    std::vector<char> result(static_cast<size_t>(pos));

    ifs.seekg(0, ios::beg);
    ifs.read(result.data(), pos);

    return result;
}

std::string read_file(const std::string& filepath) {
    std::ifstream file(filepath);
    std::stringstream ss;
    ss << file.rdbuf();
    string content = ss.str();

    return content;
}

string filename(const string& path) {
    std::experimental::filesystem::path filepath(path);
    return filepath.filename().string();
}

}
