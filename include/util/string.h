#pragma once

#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

namespace ABB::OptiMold::Utils {

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
}
