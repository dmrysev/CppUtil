#include "util/filesystem.h"

namespace Util {

std::filesystem::path getDirectoryPath(const std::string& filePath) {
    auto path = std::filesystem::path{filePath};
    return path.remove_filename();
}

}
