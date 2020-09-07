#pragma once

#include <vector>
#include <string>

namespace ABB::OptiMold::Utils {

    // float to uint32_t
    inline uint32_t ftou32(float value) {
        return *reinterpret_cast<uint32_t*>(&value);
    }
    
    // uint32_t to float
    inline float u32tof(uint32_t value) {
        return *reinterpret_cast<float*>(&value);
    }

    // bytes to numeric value
    // bytes array must be equal or more than sizeof(T)
    template<typename T>
    void bton(const uint8_t *bytes, T &out) {
        for (int i = 0; i < sizeof(T); ++i) {
            out = (out << 8) + bytes[i];
        }
    }

    // bytes to float
    inline void btof(const uint8_t *bytes, float &out) {
        uint32_t temp;
        bton(bytes, temp);
        out = u32tof(temp);
    }

    // bytes to string array
    inline std::vector<std::string> btosa(const std::vector<uint8_t> &bytes) {
        std::vector<std::string> result;

        std::string str = "";
        for (auto &c : bytes) {
            if (c == '\0') {
                result.push_back(str);
                str = "";
            } else {
                str += c;
            }
        }
        
        if (bytes.back() != '\0') {
            result.push_back(str);
        }

        return result;
    }

}
