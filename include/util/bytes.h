#pragma once

#include <vector>
#include <string>

namespace Util {

    template<typename To, typename From>
    struct alias_cast_t
    {
        union
        {
            From raw;
            To data;
        };
    };

    template<typename To, typename From>
    To alias_cast(From raw_data)
    {
        static_assert(sizeof(To) == sizeof(From), "Cannot cast types of different sizes");
        alias_cast_t<To, From> ac;
        ac.raw = raw_data;
        return ac.data;
    }

    // float to uint32_t
    inline uint32_t ftou32(float value) {
        return alias_cast<uint32_t>(value);
    }
    
    // uint32_t to float
    inline float u32tof(uint32_t value) {
        return alias_cast<float>(value);
    }

    // bytes to numeric value
    template<typename T>
    T bton(const uint8_t* bytes) {
        T out = 0;
        for (size_t i = 0; i < sizeof(T); ++i) {
            out = static_cast<T>((out << 8) + bytes[i]);
        }
        return out;
    }

    // bytes to numeric value
    // bytes array must be equal or more than sizeof(T)
    template<typename T>
    void bton(const uint8_t* bytes, T& out) {
        out = bton<T>(bytes);
    }

    // bytes to float
    inline void btof(const uint8_t* bytes, float& out)
    {
        uint32_t temp = 0;
        bton(bytes, temp);
        out = alias_cast<float>(temp);
    }

    inline float btof(const uint8_t* bytes)
    {
        uint32_t temp = 0;
        bton(bytes, temp);
        return alias_cast<float>(temp);
    }

    // bytes to double
    inline void btod(const uint8_t* bytes, double& out)
    {
        uint64_t temp = 0;
        bton(bytes, temp);
        out = alias_cast<double>(temp);
    }

    inline double btod(const uint8_t* bytes)
    {
        uint64_t temp = 0;
        bton(bytes, temp);
        return alias_cast<double>(temp);
    }

    inline std::string btos(const std::vector<uint8_t>& bytes)
    {
        return std::string(bytes.data(), bytes.data() + bytes.size());
    }

    // bytes to string array
    inline std::vector<std::string> btosa(const std::vector<uint8_t>& bytes) {
        std::vector<std::string> result;

        std::string str = "";
        for (uint8_t c : bytes) {
            if (c == '\0') {
                result.push_back(str);
                str = "";
            } else {
                str += static_cast<char>(c);
            }
        }
        
        if (bytes.size() > 0 && bytes.back() != '\0') {
            result.push_back(str);
        }

        return result;
    }

    // numeric vector to string
    template<typename T>
    std::string ntos(const std::vector<T> values) {
        auto bytes = reinterpret_cast<const char*>(values.data());
        auto size =  values.size() * sizeof(T) / sizeof(char);
        std::string s(bytes, bytes + size);

        return s;
    }

    // string to numeric vector
    template<typename T>
    std::vector<T> ston(const std::string& s) {
        auto array = reinterpret_cast<const T*>(s.data());
        auto size = s.size() * sizeof(char) / sizeof(T);
        std::vector<T> values(array, array + size);

        return values;
    }

}
