#include "string.h"

using std::string;
using std::vector;

namespace ABB::OptiMold::Utils {

vector<string> split(const string& text, char separator) {
    vector<string> result;

    std::stringstream ss(text);
    string segment;
    while (std::getline(ss, segment, separator)) {
        result.push_back(segment);
    }

    return result;
}



}
