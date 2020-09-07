#include "util/string.h"
#include <ctime>
#include <mutex>

using std::string;
using std::vector;

namespace Util {

vector<string> split(const string& text, char separator) {
    vector<string> result;

    std::stringstream ss(text);
    string segment;
    while (std::getline(ss, segment, separator)) {
        result.push_back(segment);
    }

    return result;
}

string random_string() {
    static const string charList = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const int charListSize = static_cast<int>(charList.size());
    static std::once_flag flag;
    std::call_once(flag, [] { srand(time(NULL)); });

    string alphanumeric = "";
    for(int i = 0; i < 16; i++) {
        auto index = static_cast<size_t>(rand() % charListSize);
        alphanumeric += charList[index];
    }

    return alphanumeric;
}

}
