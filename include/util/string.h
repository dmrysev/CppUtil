#pragma once

#include <vector>
#include <string>
#include <regex>
#include <boost/lexical_cast.hpp>

namespace Util {

// Split string by separator
std::vector<std::string> split(const std::string& text, char separator);

template<typename T>
std::string join(const std::vector<T>& values, std::string delim) {
    if(values.empty()) {
        return "";
    }

    std::stringstream ss;
    ss << values[0];

    for(size_t i = 1; i < values.size(); i++) {
        ss << delim << values[i];
    }

    return ss.str();
}

// String to any numeric value
template<typename T>
bool ston(const std::string& s, T& out) {
    bool result = false;

    if (!s.empty()) {
        try {
            out = boost::lexical_cast<T>(s);
            result = true;
        } catch (const boost::bad_lexical_cast&) { }
    }

    return result;
}

inline bool starts_with(const std::string& base, const std::string& token)
{
    return base.compare(0, token.size(), token) == 0;
}

// this function copy full orig string to destination if
// size of orig is less than n, otherwise will copy only
// n characters
inline void copy_max(const std::string& orig, size_t n, char* dest)
{
    strncpy(dest, orig.c_str(), orig.size() < n ? orig.size() + 1 : n);
}

// replace all occurance of findStr in str to replaceStr
inline void replace_all(std::string& str, std::string findStr, std::string replaceStr)
{
    for (size_t pos = str.find(findStr);
         pos != std::string::npos;
         pos = str.find(findStr, pos + findStr.size() + replaceStr.size()))
    {
        str.replace(pos, findStr.size(), replaceStr);
    }
}

// implement glob matching via regex
// seq "/var/bar/42" will match pattern "/var/bar/*"
inline bool glob_match(std::string pattern, const std::string& seq)
{
    replace_all(pattern, "/", "\\/?");
    replace_all(pattern, "*", ".*");
    return std::regex_match(seq, std::regex{pattern});
}

std::string random_string();

}
